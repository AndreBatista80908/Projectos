-- a) Qual o nome do fornecedor que forneceu o maior número de categorias? Note que pode ser mais do que um fornecedor.
WITH FornCateg(nif, categoria) as (
	(SELECT P.forn_primario as nif, P.categoria
	 FROM produto P) UNION
	(SELECT Fs.nif, P.categoria
	 FROM produto P NATURAL JOIN fornece_sec Fs))
SELECT Final.nome
FROM (fornecedor NATURAL JOIN FornCateg) as Final
GROUP BY Final.nome
HAVING count(DISTINCT Final.categoria) >=all (
	SELECT count(DISTINCT FornCateg.categoria)
	FROM FornCateg
	GROUP BY FornCateg.nif);

-- b) Quais os fornecedores primários (nome e nif) que forneceram produtos de todas as categorias simples?
SELECT F.nome, F.nif
FROM fornecedor F, produto P, categoria_simples C
WHERE F.nif = P.forn_primario and C.nome = P.categoria
GROUP BY F.nome, F.nif
HAVING count(DISTINCT P.categoria) = (
	SELECT count(*)
	FROM categoria_simples);

-- c) Quais os produtos (ean) que nunca foram repostos?
SELECT P.ean
FROM produto P
WHERE P.ean not in(
	(SELECT R.ean
	 FROM reposicao R));

-- d) Quais os produtos (ean) com um número de fornecedores secundários superior a 10?
SELECT ean
FROM produto NATURAL JOIN fornece_sec
GROUP BY ean
HAVING count(DISTINCT nif) > 10;

-- e) Quais os produtos (ean) que foram repostos sempre pelo mesmo operador?
SELECT ean
FROM reposicao
GROUP BY ean
HAVING count(DISTINCT operador) = 1;
