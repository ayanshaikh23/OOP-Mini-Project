const express = require('express');
const fs = require('fs');
const path = require('path');
const cors = require('cors');

const app = express();
const PORT = 3000;

app.use(cors());
app.use(express.json());

// Serve frontend HTML files from the serverfile folder
app.use(express.static(path.join(__dirname)));

// ─── PATH TO LEDGER FOLDER (where C++ reads/writes files) ───
// __dirname = serverfile folder
// '../ledger' = goes up one level, then into ledger folder
const LEDGER_DIR = path.join(__dirname, '..', 'ledger');

// ─── HELPERS ────────────────────────────────────────────────

function usersFile()           { return path.join(LEDGER_DIR, 'users.txt'); }
function itemsFile(username)   { return path.join(LEDGER_DIR, `${username}_items.txt`); }
function txFile(username)      { return path.join(LEDGER_DIR, `${username}_transactions.txt`); }
function profileFile(username) { return path.join(LEDGER_DIR, `${username}_profile.txt`); }

function readLines(filePath) {
  if (!fs.existsSync(filePath)) return [];
  return fs.readFileSync(filePath, 'utf8')
    .split('\n')
    .map(l => l.replace(/\r/g, '').trim())  // ← removes \r on Windows
    .filter(l => l !== '');
}

function getAutoDate() {
  const now = new Date();
  return `${now.getDate()}/${now.getMonth() + 1}/${now.getFullYear()}`;
}

// ─── AUTH ────────────────────────────────────────────────────

// POST /login
app.post('/login', (req, res) => {
  const { username, password } = req.body;
  if (!username || !password)
    return res.json({ success: false, message: 'Missing credentials.' });

  const lines = readLines(usersFile());
  const found = lines.find(line => {
    const [u, p] = line.split(',');
    return u === username && p === password;
  });

  if (found) return res.json({ success: true });
  res.json({ success: false, message: 'Invalid username or password.' });
});

// POST /register
app.post('/register', (req, res) => {
  const { username, password } = req.body;
  if (!username || !password)
    return res.json({ success: false, message: 'Missing fields.' });

  const lines = readLines(usersFile());
  const exists = lines.some(line => line.split(',')[0] === username);
  if (exists)
    return res.json({ success: false, message: 'Username already exists.' });

  fs.appendFileSync(usersFile(), `${username},${password}\n`);
  res.json({ success: true });
});

// ─── DASHBOARD ───────────────────────────────────────────────

// GET /dashboard?username=xxx
app.get('/dashboard', (req, res) => {
  const { username } = req.query;
  if (!username) return res.json({ error: 'Missing username' });

  const lines = readLines(txFile(username));
  let balance = 0, credited = 0, debited = 0, creditCount = 0, debitCount = 0;

  lines.forEach(line => {
    const parts = line.split(',');
    if (parts.length < 3) return;
    const type = parts[0].trim();
    const amount = parseFloat(parts[2]);
    if (isNaN(amount)) return;

    if (type === 'credit') {
      credited += amount;
      balance  += amount;
      creditCount++;
    } else if (type === 'debit') {
      debited += amount;
      balance -= amount;
      debitCount++;
    }
  });

  res.json({ balance, credited, debited, creditCount, debitCount });
});

// ─── TRANSACTIONS ─────────────────────────────────────────────

// GET /transactions?username=xxx&limit=5
app.get('/transactions', (req, res) => {
  const { username, limit } = req.query;
  if (!username) return res.json({ transactions: [] });

  const lines = readLines(txFile(username));
  const parsed = lines.map(line => {
    const parts = line.split(',');
    if (parts.length < 6) return null;
    return {
      type:   parts[0].trim(),
      item:   parts[1].trim(),
      amount: parseFloat(parts[2]),
      method: parts[3].trim(),
      desc:   parts[4].trim(),
      date:   parts[5].trim()
    };
  }).filter(Boolean).reverse(); // newest first

  const result = limit ? parsed.slice(0, parseInt(limit)) : parsed;
  res.json({ transactions: result });
});

// POST /transaction
app.post('/transaction', (req, res) => {
  const { username, item, amount, type, method, description } = req.body;
  if (!username || !item || !amount || !type)
    return res.json({ success: false, message: 'Missing fields.' });

  const date = getAutoDate();
  const line = `${type},${item},${amount},${method || 'cash'},${description || ''},${date}\n`;
  fs.appendFileSync(txFile(username), line);
  res.json({ success: true });
});

// ─── ITEMS ────────────────────────────────────────────────────

// GET /items?username=xxx
app.get('/items', (req, res) => {
  const { username } = req.query;
  if (!username) return res.json({ items: [] });

  const items = readLines(itemsFile(username));
  res.json({ items });
});

// POST /items
app.post('/items', (req, res) => {
  const { username, item } = req.body;
  if (!username || !item)
    return res.json({ success: false, message: 'Missing fields.' });

  const existing = readLines(itemsFile(username));
  if (existing.includes(item.trim()))
    return res.json({ success: false, message: 'Item already exists.' });

  fs.appendFileSync(itemsFile(username), `${item.trim()}\n`);
  res.json({ success: true });
});

// ─── PROFILE ─────────────────────────────────────────────────

// GET /profile?username=xxx
app.get('/profile', (req, res) => {
  const { username } = req.query;
  if (!username) return res.json({});

  const lines = readLines(profileFile(username));
  res.json({
    companyName:   lines[0] || '',
    ownerName:     lines[1] || '',
    address:       lines[2] || '',
    contactNumber: lines[3] || '',
    email:         lines[4] || '',
    businessType:  lines[5] || ''
  });
});

// POST /profile
app.post('/profile', (req, res) => {
  const { username, companyName, ownerName, address, contactNumber, email, businessType } = req.body;
  if (!username) return res.json({ success: false, message: 'Missing username.' });

  const content = [companyName, ownerName, address, contactNumber, email, businessType]
    .map(v => (v || '').replace(/\n/g, ' '))
    .join('\n') + '\n';

  fs.writeFileSync(profileFile(username), content);
  res.json({ success: true });
});

// ─── START ────────────────────────────────────────────────────

app.listen(PORT, () => {
  console.log(`\n✅ Business Ledger Server running at http://localhost:${PORT}`);
  console.log(`   Open http://localhost:${PORT}/login.html in your browser\n`);
  console.log(`   Reading/Writing files from: ${LEDGER_DIR}\n`);
});
