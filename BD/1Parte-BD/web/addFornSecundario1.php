<html>
    <head>
        <meta charset="UTF-8">
    </head>
	<link rel="stylesheet" type="text/css" href="mystyle.css">
    <body>

        <p><h3>Adicionar Fornecedor Secundário:</h3></p>
        <form action="addFornSecundario2.php" method="post">
            <p><input type="hidden" name="ean" value="<?=$_REQUEST['ean']?>" /></p>
            Nome do fornecedor Secundário: 
            <input type="text" name="nome"/>
            <br>
            Nif do fornecedor Secundário: 
            <input type="text" name="nif"/>
            <br>
            <input type="submit" value="Adicionar"/>
        </form>

    <button><a href="homePageProdutos.php">Voltar para a Home Page</a></button>

    </body>
</html>