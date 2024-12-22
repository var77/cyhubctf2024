const express = require('express');
const { Client } = require('pg');

const app = express();
const port = 8080;

const client = new Client({
  user: 'app_user',
  host: 'localhost',
  database: 'postgres',
  password: process.env.APP_USER_PASSWORD,
  port: 5432,
});

client.connect();

app.get('/', (_, res) => res.sendFile(__dirname + '/index.html'));

app.get('/messages', async (req, res) => {
  const { id } = req.query;

  try {

    if (parseInt(id) === '1337') {
      return res.status(403).end();
    }

    let result = [];
    if (!id) {
      result = (await client.query('SELECT * FROM get_messages() WHERE id != 1337')).rows;
    } else {
      result = (await client.query('SELECT * FROM get_message($1)', [id])).rows.map(row => ({ id: 0, msg: '', img: row.img }));
    }

    res.json({ messages: result }).end();
  } catch (err) {
    console.error('Error querying PostgreSQL:', err);
    res.status(500).json({ error: 'Internal Server Error' });
  }
});

app.listen(port, '0.0.0.0', () => {
  console.log(`Server is running on http://localhost:${port}`);
});
