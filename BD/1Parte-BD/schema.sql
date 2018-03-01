-- Schema
drop table if exists categoria cascade;
drop table if exists categoria_simples cascade;
drop table if exists super_categoria cascade;
drop table if exists constituida cascade;
drop table if exists fornecedor cascade;
drop table if exists produto cascade;
drop table if exists fornece_sec cascade;
drop table if exists corredor cascade;
drop table if exists prateleira cascade;
drop table if exists planograma cascade;
drop table if exists evento_reposicao cascade;
drop table if exists reposicao cascade;

create table categoria
   (nome 	varchar(30) 	not null,
    constraint 	pk_categoria 	primary key(nome));

create table categoria_simples
   (nome 	varchar(30)		not null,
    constraint 	pk_categoria_simples       		primary key(nome),
    constraint 	fk_categoria_simples_categoria 	foreign key(nome) 	references categoria(nome));

create table super_categoria
   (nome 	varchar(30)		not null,
    constraint 	pk_super_categoria 			  primary key(nome),
    constraint 	fk_super_categoria_categoria  foreign key(nome) 	references categoria(nome));

create table constituida
   (super_categoria   varchar(30)		not null,
   	categoria 		  varchar(30)		not null,
    constraint 	pk_constituida 					primary key(super_categoria, categoria),
    constraint 	fk_constituida_super_categoria  foreign key(super_categoria) 	references super_categoria(nome),
    constraint 	fk_constituida_categoria 		foreign key(categoria) 			references categoria(nome));

create table fornecedor
   (nif   numeric(9,0)  not null,
    nome  varchar(30)   not null,
    constraint  pk_fornecedor   primary key(nif));

create table produto
   (ean 			numeric(13,0)  not null,
   	design 			varchar(30)	   not null,
   	categoria 	   	varchar(30)	   not null,
   	forn_primario 	numeric(9,0)   not null,
   	data 			date           not null,
    constraint 	pk_produto 				primary key(ean),
    constraint 	fk_produto_categoria  	foreign key(categoria)		references categoria(nome),
    constraint 	fk_produto_fornecedor 	foreign key(forn_primario) 	references fornecedor(nif));

create table fornece_sec
   (nif 	numeric(9,0) 	 not null,
   	ean 	numeric(13,0)	 not null,
    constraint 	pk_fornece_sec 				primary key(nif, ean),
    constraint 	fk_fornece_sec_fornecedor   foreign key(nif)	references fornecedor(nif),
    constraint 	fk_fornece_sec_produto 		foreign key(ean) 	references produto(ean));

create table corredor
   (nro 		numeric(2,0) 	not null,
	largura 	numeric(3,0)	not null,
	constraint 	pk_corredor 	primary key(nro));

create table prateleira
   (nro 	numeric(2,0)   not null,
   	lado 	char(10)	   not null,
   	altura 	char(10)       not null,
    constraint 	pk_prateleira		    primary key(nro, lado, altura),
    constraint 	fk_prateleira_corredor 	foreign key(nro) 	references corredor(nro));

create table planograma
   (ean 	   numeric(13,0)  not null,
   	nro 	   numeric(2,0)	  not null,
   	lado 	   char(10)		  not null,
   	altura 	   char(10)   	  not null,
   	face 	   numeric(2,0)   not null,
   	unidades   numeric(2,0)   not null,
   	loc 	   numeric(2,0)   not null,
    constraint 	pk_planograma				primary key(ean, nro, lado, altura),
    constraint 	fk_planograma_produto 		foreign key(ean) 				references produto(ean),
    constraint 	fk_planograma_prateleira 	foreign key(nro, lado, altura) 	references prateleira(nro, lado, altura));

create table evento_reposicao
   (operador 	numeric(9,0) 	not null,
   	instante 	date        	not null,
    constraint 	pk_evento_reposicao 	primary key(operador, instante));

create table reposicao
   (ean 		numeric(13,0)   not null,
   	nro 		numeric(2,0)	not null,
   	lado 		char(10) 		not null,
   	altura 		char(10)  	    not null,
   	operador 	numeric(9,0) 	not null,
   	instante 	date 	        not null,
   	unidades 	numeric(2,0)    not null,
    constraint 	pk_preposicao					primary key(ean, nro, lado, altura, operador, instante),
    constraint 	fk_reposicao_planograma 		foreign key(ean, nro, lado, altura) 	references planograma(ean, nro, lado, altura),
    constraint 	fk_reposicao_evento_reposicao 	foreign key(operador, instante) 		references evento_reposicao(operador, instante));
