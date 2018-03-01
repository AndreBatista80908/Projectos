-- MODELO​ MULTIDIMENSIONAL

-- POPULATE d_produto
INSERT INTO d_produto
	SELECT ean, categoria, forn_primario
	FROM produto;

-- POPULATE d_tempo
INSERT INTO d_tempo
    SELECT distinct instante, date_part('day',instante), date_part('month',instante), date_part('year',instante)
    FROM evento_reposicao;

-- POPULATE fact_reposicao
INSERT INTO fact_reposicao
	SELECT P.ean, T.data, R.unidades
    FROM d_produto P, d_tempo T, reposicao R
    WHERE P.ean = R.ean and T.data = R.instante;