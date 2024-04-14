'use strict';
var express = require('express');
var router = express.Router();

// Rutas para la captura de un formulario
app.get('/formulario', (req, res) => {
    res.send('Mostrar formulario');
});

app.post('/formulario', (req, res) => {
    const { nombre, email } = req.body;
    // Procesar los datos del formulario
    res.send(`Datos recibidos: Nombre - ${nombre}, Email - ${email}`);
});

module.exports = router;
