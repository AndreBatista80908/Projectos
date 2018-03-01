-- DATA ANALYTICS

-- ROLLUP
SELECT categoria, ano, mes, count(ean) as numero_reposicoes 
FROM fact_reposicao NATURAL JOIN d_produto NATURAL JOIN d_tempo
GROUP BY ROLLUP (categoria, ano, mes)
WHERE nif_fornecedor_principal = '123​455678'
ORDER BY ano desc, mes desc, categoria, numero_reposicoes;

-- GROUPING SETS
SELECT categoria, ano, mes, count(ean) as numero_reposicoes 
FROM fact_reposicao NATURAL JOIN d_produto NATURAL JOIN d_tempo
GROUP BY GROUPING SETS ( (categoria, ano, mes), (categoria, ano), (categoria), () )
WHERE nif_fornecedor_principal = '123​455678'
ORDER BY ano desc, mes desc, categoria, numero_reposicoes;

-- UNION
(SELECT categoria, ano, mes, count(ean) as numero_reposicoes 
FROM fact_reposicao NATURAL JOIN d_produto NATURAL JOIN d_tempo
WHERE nif_fornecedor_principal = '123​455678'
GROUP BY categoria, ano, mes)
UNION
(SELECT categoria, ano, null, count(ean) as numero_reposicoes 
FROM fact_reposicao NATURAL JOIN d_produto NATURAL JOIN d_tempo
WHERE nif_fornecedor_principal = '123​455678'
GROUP BY categoria, ano)
UNION
(SELECT categoria, null, null, count(ean) as numero_reposicoes 
FROM fact_reposicao NATURAL JOIN d_produto NATURAL JOIN d_tempo
WHERE nif_fornecedor_principal = '123​455678'
GROUP BY categoria)
UNION
(SELECT null, null, null, count(ean) as numero_reposicoes 
FROM fact_reposicao NATURAL JOIN d_produto NATURAL JOIN d_tempo
WHERE nif_fornecedor_principal = '123​455678')
ORDER BY ano desc, mes desc, categoria, numero_reposicoes;
