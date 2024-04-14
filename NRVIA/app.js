'use strict';

const cluster               = require('cluster');
const os                    = require('os');
const https                 = require('https');
const fs                    = require('fs');
const express               = require('express');
const path                  = require('path');
const morgan                = require('morgan');
const cookieParser          = require('cookie-parser');
const bodyParser            = require('body-parser');
const swaggerStats          = require('swagger-stats');
const promClient            = require('prom-client');
const AggregatorRegistry    = promClient.AggregatorRegistry;
const yargs                 = require('yargs');
const pug = require('pug'); // Requerir pug

const { execFile } = require('node:child_process');
const child = execFile('node', ['--version'], (error, stdout, stderr) => {
    if (error) {
        throw error;
    }
    console.log(stdout);
}); 


if (cluster.isMaster)
{
    const numCPUs = os.cpus().length;
    console.log(`Master ${process.pid} is running`);

    // Crea un worker para cada CPU
    for (let i = 0; i < numCPUs; i++) {
        cluster.fork();
    }

    cluster.on('exit', (worker, code, signal) => {
        console.log(`Worker ${worker.process.pid} died`);
    });
}
else
{
    const app = express();
    app.use(morgan('combined'));
    app.use(bodyParser.json());
    app.use(swaggerStats.getMiddleware());

    
    // view engine setup
    app.set('views', path.join(__dirname, 'views'));
    app.set('view engine', 'pug'); // Configurar pug como motor de plantillas

    var routes = require('./routes/index');
    var users = require('./routes/users');

    // uncomment after placing your favicon in /public
    //app.use(favicon(__dirname + '/public/favicon.ico'));
    //app.use(logger('dev'));
    //app.use(bodyParser.json());
    app.use(bodyParser.urlencoded({ extended: false }));
    app.use(cookieParser());
    app.use(express.static(path.join(__dirname, 'public')));

    app.use('/', routes);
    app.use('/users', users);

    // catch 404 and forward to error handler    
    app.use(function (req, res, next) {
        var err = new Error('Not Found');
        err.status = 404;
        next(err);
    });

    // development error handler
    // will print stacktrace
    if (app.get('env') === 'development')
    {
        app.use(function (err, req, res, next)
        {
            res.status(err.status || 500);
            res.render('error', {
                message: err.message,
                error: err
            });
        });
    }

    // production error handler
    // no stacktraces leaked to user
    app.use(function (err, req, res, next)
    {
        res.status(err.status || 500);
        res.render('error', {
            message: err.message,
            error: {}
        });
    });

    // Los workers pueden compartir cualquier conexión TCP
    // En este caso, es un servidor HTTPS
    https.createServer({
        //key: fs.readFileSync('server.key'),
        //cert: fs.readFileSync('server.cert')
    }, app).listen(4000, () => {
        console.log(`Worker ${process.pid} started`);
    });
}