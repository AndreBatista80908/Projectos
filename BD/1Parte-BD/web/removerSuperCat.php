<html>
    <head>
      <meta charset="UTF-8">
    </head>
    <link rel="stylesheet" type="text/css" href="mystyle.css">
    <body>
<?php
    $nome = $_REQUEST['nome'];
    try
    {
        $host = "db.ist.utl.pt";
        $user ="ist180908";
        $password = "fbqs8304";
        $dbname = $user;
        $db = new PDO("pgsql:host=$host;dbname=$dbname", $user, $password);
        $db->setAttribute(PDO::ATTR_ERRMODE, PDO::ERRMODE_EXCEPTION);

        $db->query("start transaction;");

        /*Caso a Super Categoria que estamos a remover seja Sub-Categoria de outra Super Categoria*/
        $sql = "SELECT count(super_categoria) FROM constituida GROUP BY super_categoria, categoria HAVING categoria = :nome;";
        $result = $db->prepare($sql);
        $result->execute([':nome' => $nome]);
        $contador = $result->fetch();

        if($contador[0] >= 1)
        {
            /*Ligação entre a Super Categoria e a Sub-Categoria desta Super Categoria*/
            $sql = "SELECT super_categoria FROM constituida WHERE categoria = :nome;";
            $result = $db->prepare($sql);
            $result->execute([':nome' => $nome]);
            $temp = $result->fetch();
            $nomeSupCat = $temp[0];

            $sql = "SELECT categoria FROM constituida WHERE super_categoria = :nome;";
            $result = $db->prepare($sql);
            $result->execute([':nome' => $nome]);
            $temp = $result->fetch();
            $nomeSubCat = $temp[0];

            $sql = "INSERT INTO constituida VALUES (:nomeSupCat, :nomeSubCat);";
            $result = $db->prepare($sql);
            $result->execute([':nomeSupCat' => $nomeSupCat, ':nomeSubCat' => $nomeSubCat]);

            $sql = "DELETE FROM constituida WHERE categoria = :nome OR super_categoria = :nome;";
            $result = $db->prepare($sql);
            $result->execute([':nome' => $nome]);
        }

        $sql = "DELETE FROM reposicao WHERE exists(SELECT ean FROM reposicao NATURAL JOIN produto WHERE exists (SELECT ean FROM produto WHERE categoria = :nome));";
        $result = $db->prepare($sql);
        $result->execute([':nome' => $nome]);

        $sql = "DELETE FROM planograma WHERE exists (SELECT ean FROM planograma NATURAL JOIN produto WHERE exists (SELECT ean FROM produto WHERE categoria = :nome));";
        $result = $db->prepare($sql);
        $result->execute([':nome' => $nome]);

        $sql = "DELETE FROM fornece_sec WHERE exists (SELECT ean FROM fornece_sec NATURAL JOIN produto WHERE exists (SELECT ean FROM produto WHERE categoria = :nome));";
        $result = $db->prepare($sql);
        $result->execute([':nome' => $nome]);

        $sql = "DELETE FROM produto WHERE categoria = :nome;";
        $result = $db->prepare($sql);
        $result->execute([':nome' => $nome]);

        $sql = "DELETE FROM super_categoria WHERE nome = :nome";
        $result = $db->prepare($sql);
        $result->execute([':nome' => $nome]);

        $sql = "DELETE FROM categoria WHERE nome = :nome;";
        $result = $db->prepare($sql);
        $result->execute([':nome' => $nome]);

        echo("<p>Categoria $nome removida</p>");

        $db->query("commit;");

        $db = null;
    }
    catch (PDOException $e)
    {
        $db->query("rollback;");
        echo("<p>ERROR: {$e->getMessage()}</p>");
    }
?>
    <button><a href="homePageCategorias.php">Voltar para a Home Page</a></button>
    
    </body>
</html>