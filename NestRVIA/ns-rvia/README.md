<p align="center">
  <a href="http://nestjs.com/" target="blank"><img src="https://nestjs.com/img/logo-small.svg" width="200" alt="Nest Logo" /></a>
</p>
# API de RVIA.

1. Clonar proyecto
2. ``` yarn install ```
3. Clonar el archivo ``` .env.template ``` y renombrarlo a ``` .env ```.
4. Cambiar las variables de ambiente.
5. Levantar la base de datos de docker si está instalado
```
  docker-compose up -d
```
6. Levantar el servicio de Nest
```
yarn run start:dev
```
7. Ejecutar SEED 
```
http://127.0.0.1:4001/api/seed
```