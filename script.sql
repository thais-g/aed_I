DROP DATABASE agenda_dados;
SHOW DATABASES;
CREATE DATABASE agenda_dados;
USE agenda_dados;
CREATE TABLE contatos ( nome varchar(30) Not Null, tel varchar(30) Not Null ) Default charset = utf8;
CREATE TABLE tarefas ( texto text Not Null, chave int Not Null ) Default charset = utf8;

SHOW DATABASES;