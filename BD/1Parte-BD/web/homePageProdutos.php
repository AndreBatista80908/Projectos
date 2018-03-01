<html>
    <head>
        <meta charset="UTF-8">
    </head>
	<link rel="stylesheet" type="text/css" href="mystyle.css">
    <body>
        <h3 style=" text-align: center; padding-top: 1%; padding-bottom: 1%; border-color: black; border-style: solid; background-color: white; color: black;">Projeto de Bases de Dados - Parte 3 (Grupo 33)<br>Heydi Marques&nbsp;nº 79062<br>André Batista&nbsp;&nbsp;&nbsp;nº 80908<br>Sandro Anjos&nbsp;&nbsp;&nbsp;nº 82396</h3>

        <p><h3>Adicionar Produto:</h3></p>
        <form action="adicionarProduto.php" method="post">
            Ean: 
            <input type="text" name="ean"/> &nbsp;&nbsp;&nbsp;
            Designação: 
            <input type="text" name="design"/> &nbsp;&nbsp;&nbsp;
            Categoria: 
            <input type="text" name="categoria"/> &nbsp;&nbsp;&nbsp;
            <br>
            Nome do fornecedor Primário: 
            <input type="text" name="nome"/> &nbsp;&nbsp;&nbsp;
            Nif do fornecedor Primário: 
            <input type="text" name="forn_primario"/>
            <input style="margin-left: 10px;" type="submit" name="Adicionar"/>
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
    
        $sql = "SELECT * FROM produto; ";
        $result = $db->prepare($sql);
        $result->execute();

        echo("<p><h3>Produtos:</h3></p>");

        echo("<table border=\"0\" cellspacing=\"5\">\n");
        foreach($result as $row)
        {
            echo("<tr>\n");
            echo("<td>{$row['design']}</td>\n");
            echo("<td>
                <form action=\"updateDesign.php\" method=\"post\">
                    <p><input type=\"hidden\" name=\"ean\" value=\"{$row['ean']}\" /></p>
                    <p style=\"margin-top: 1px;\">Nova designação: <input type=\"text\" name=\"design\"/> <input type=\"submit\" value=\"Update\"/></p>
                </form>
            </td>\n");
            echo("<td><button><a href=\"addFornSecundario1.php?ean={$row['ean']}\">Adicionar Fornecedor Secundário</a></button></td>\n");
            echo("<td><button><a href=\"listarEventosReposicao.php?ean={$row['ean']}\">Listar Eventos de Reposição</a></button></td>\n");
            echo("<td><button><a href=\"removerProduto.php?ean={$row['ean']}\">Remover</a></button></td>\n");
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