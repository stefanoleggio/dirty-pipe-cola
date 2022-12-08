'use strict';

const express = require('express');
const logger = require('morgan');
const fs = require('fs');
const path = require('path');

// Constants
const PORT = 8080;
const HOST = '0.0.0.0';
const ZOOM_PATH = path.resolve(__dirname, 'zoom')

// App
const app = express();
app.use(express.json());
app.use(express.urlencoded({ extended: true }));

app.listen(PORT, HOST, () => {
	console.log(`Running on http://${HOST}:${PORT}`);
});

app.get('/', (req, res) => {
	res.sendFile(ZOOM_PATH+"/Launch Meeting - Zoom.html");
});
