-- RESTRICOES DE INTEGRIDADE

-- a) O fornecedor (primario) de um produto nao pode existir na relacao fornece_sec para o mesmo produto.

create or replace function soFornPrimario() returns trigger
as $$
	declare nifPrim numeric;
	begin
		SELECT forn_primario INTO nifPrim FROM produto P WHERE P.ean = new.ean;
		if new.nif = nifPrim then
			raise exception 'O fornecedor % já é o fornecedor primário de %.', new.nif, new.ean;
		end if;
		return new;
	end
$$ language plpgsql;

drop trigger if exists soFornPrimario_trigger on fornece_sec;

create trigger soFornPrimario_trigger before insert or update on fornece_sec
for each row execute procedure soFornPrimario();

-- Query de teste:
-- INSERT INTO fornece_sec VALUES ('784623800', '1425630255816');
-- UPDATE fornece_sec SET nif = '784623800' WHERE ean = '1425630255816';

-----------------------------------------------------------------------------------------------------------------------------

-- a) O fornecedor (primario) de um produto nao pode existir na relacao fornece_sec para o mesmo produto.

create or replace function jaFornSecundario() returns trigger
as $$
	declare nifSec numeric;
	begin
		SELECT nif INTO nifSec FROM fornece_sec F WHERE F.ean = new.ean;
		if new.forn_primario = nifSec then
			raise exception 'O fornecedor % já é o fornecedor secundário de %.', new.forn_primario, new.ean;
		end if;
		return new;
	end
$$ language plpgsql;

drop trigger if exists jaFornSecundario_trigger on produto;

create trigger jaFornSecundario_trigger before update on produto
for each row execute procedure jaFornSecundario();

-- Query de teste:
-- UPDATE produto SET forn_primario = '739124030' WHERE ean = '1425630255816';

-----------------------------------------------------------------------------------------------------------------------------

-- b) O instante mais recente de reposicao tem de ser sempre anterior ou igual a data atual.

create or replace function instanteEvento() returns trigger
as $$
	declare data date;
	begin
		SELECT CURRENT_DATE INTO data;
		if new.instante > data then
			raise exception 'Instante de reposição (%) superior à data atual.', new.instante;
		end if;
		return new;
	end
$$ language plpgsql;

drop trigger if exists instanteEvento_trigger on evento_reposicao;

create trigger instanteEvento_trigger before insert or update on evento_reposicao
for each row execute procedure instanteEvento();

-- Query de teste:
-- INSERT INTO evento_reposicao VALUES ('241088861','2018-12-01');
-- UPDATE evento_reposicao SET instante = '2018-12-01' WHERE instante = '2017-09-20';