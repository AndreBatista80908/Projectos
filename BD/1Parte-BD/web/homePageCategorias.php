<html>
    <head>
      <meta charset="UTF-8">
    </head>
	<link rel="stylesheet" type="text/css" href="mystyle.css">
    <body>
        <h3 style=" text-align: center; padding-top: 1%; padding-bottom: 1%; border-color: black; border-style: solid; background-color: white; color: black;">Projeto de Bases de Dados - Parte 3 (Grupo 33)<br>Heydi Marques&nbsp;nº 79062<br>André Batista&nbsp;&nbsp;&nbsp;nº 80908<br>Sandro Anjos&nbsp;&nbsp;&nbsp;nº 82396</h3>

        <p><h3>Adicionar Categoria Simples:</h3></p>
        <form action="adicionarCatSimp.php" method="post">
            Categoria: 
            <input type="text" name="nome"/>
            <input type="submit" value="Adicionar"/>
        </form>

<?php
    try
    {
        $host = "db.ist.utl.pt";
        $user ="ist180908";
        $password = "fbqs8304";
        $dbname = $user;
        $db = new PDO("pgsql:host=$host;dbname=$dbname", $user, $password);
        $db->setAttribute(PDO::ATTR_ERRMODE, PDO::ERRMODE_EXCEPTION);

        $db->query("start transaction;");
    
        $sql = "SELECT * FROM super_categoria; ";
        $result = $db->prepare($sql);
        $result->execute();

        echo("<p><h3>Super Categorias:</h3></p>");

        echo("<table border=\"0\" cellspacing=\"5\">\n");
        foreach($result as $row)
        {
            echo("<tr>\n");
            echo("<td>{$row['nome']}</td>\n");
            echo("<td><button><a href=\"super_adicionarSubCat1.php?nome={$row['nome']}\">Adicionar sub-categoria</a></button></td>\n");
            echo("<td><button><a href=\"listarSubCategorias.php?nome={$row['nome']}\">Listar sub-categorias</a></button></td>\n");
            echo("<td><button><a href=\"removerSuperCat.php?nome={$row['nome']}\">Remover</a></button></td>\n");
            echo("</tr>\n");
        }
        echo("</table>\n");

        $sql = "SELECT * FROM categoria_simples; ";
        $result = $db->prepare($sql);
        $result->execute();

        echo("<p><h3>Categorias Simples:</h3></p>");

        echo("<table border=\"0\" cellspacing=\"5\">\n");
        foreach($result as $row)
        {
            echo("<tr>\n");
            echo("<td>{$row['nome']}</td>\n");
            echo("<td><button><a href=\"simples_adicionarSubCat1.php?nome={$row['nome']}\">Adicionar sub-categoria</a></button></td>\n");
            echo("<td><button><a href=\"removerCatSimp.php?nome={$row['nome']}\">Remover</a></button></td>\n");
            echo("</tr>\n");
        }
        echo("</table>\n");

        $db->query("commit;");

        $db = null;
    }
    catch (PDOException $e)
    {
        $db->query("rollback;");
        echo("<p>ERROR: {$e->getMessage()}</p>");
    }
?>

    </body>
</html>