-- MODELO​ MULTIDIMENSIONAL

drop table if exists d_produto cascade;
drop table if exists d_tempo cascade;
drop table if exists fact_reposicao cascade;

create table d_produto
   (ean 						numeric(13,0)  not null,
   	categoria 	   				varchar(30)	   not null,
   	nif_fornecedor_principal 	numeric(9,0)   not null,
    constraint 	pk_d_produto 	primary key(ean));

create table d_tempo
   (data	date		not null,
   	dia 	integer 	not null,
   	mes 	integer    	not null,
   	ano 	integer    	not null,
    constraint 	pk_d_tempo 	primary key(data));

create table fact_reposicao
   (ean 		numeric(13,0)  	not null,
    data		date		   	not null,
  	unidades 	numeric(2,0) 	not null,
  	idEvento	serial			not null,
	constraint 	pk_fact_reposicao 	primary key(idEvento),
	constraint 	fk_fact_reposicao_d_produto 	foreign key(ean) 	references d_produto(ean),
	constraint 	fk_fact_reposicao_d_tempo 		foreign key(data) 	references d_tempo(data));