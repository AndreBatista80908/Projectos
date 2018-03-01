-- INDICES

drop index if exists fornecedor_index;
drop index if exists produto1_index;
drop index if exists produto2_index;
drop index if exists fornece_sec_index;
drop index if exists fornece_sec2_index;
drop index if exists produto3_index;

-- 1. Liste​ ​ o ​ ​ nif​ ​ e ​ ​ nome​ ​ de​ ​ todos​ ​ os​ ​ fornecedores​ ​ primarios​ ​ da​ ​ categoria​ ​ Frutos.

create index fornecedor_index on fornecedor(nif) using hash;

create index produto1_index on produto(forn_primario) using hash;

create index produto2_index on produto(categoria) using btree;

-- 2. Liste​ ​ o ​ ​ numero​ ​ fornecedores​ ​ secundarios​ ​ de​ ​ cada​ ​ produto​ ​ com​ ​ mais​ ​ de​ ​ 1 ​ ​ fornecedor secundario.

create index fornece_sec_index on fornece_sec(nif) using btree;

create index fornece_sec2_index on fornece_sec(ean) using hash;

create index produto3_index on produto(ean) using hash;
