<html>
    <head>
      <meta charset="UTF-8">
    </head>
    <link rel="stylesheet" type="text/css" href="mystyle.css">
    <body>
<?php
    $nome = $_REQUEST['nome'];
    $nomeSubCat = $_REQUEST['nomeSubCat'];
    try
    {
        $host = "db.ist.utl.pt";
        $user ="ist180908";
        $password = "fbqs8304";
        $dbname = $user;
        $db = new PDO("pgsql:host=$host;dbname=$dbname", $user, $password);
        $db->setAttribute(PDO::ATTR_ERRMODE, PDO::ERRMODE_EXCEPTION);

        $db->query("start transaction;");
        
        $sql = "INSERT INTO categoria VALUES (:nomeSubCat) ;";
        $result = $db->prepare($sql);
        $result->execute([':nomeSubCat' => $nomeSubCat]);

        $sql = "INSERT INTO categoria_simples VALUES (:nomeSubCat) ;";
        $result = $db->prepare($sql);
        $result->execute([':nomeSubCat' => $nomeSubCat]);

        $sql = "INSERT INTO super_categoria VALUES (:nome) ;";
        $result = $db->prepare($sql);
        $result->execute([':nome' => $nome]);

        $sql = "DELETE FROM categoria_simples WHERE nome = :nome ;";
        $result = $db->prepare($sql);
        $result->execute([':nome' => $nome]);
        
        $sql = "INSERT INTO constituida VALUES (:nome, :nomeSubCat);";
        $result = $db->prepare($sql);
        $result->execute([':nome' => $nome, ':nomeSubCat' => $nomeSubCat]);

        echo("<p>Sub-Categoria $nomeSubCat adicionada</p>");

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