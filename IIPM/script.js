var justOnce = 0;

var classificacoes = {
    "pistachiosC": 3,
    "amendoinsC": 5,
    "milhoC": 2,
    "tremocosC": 4,
    "azeitonasC": 3,
    "hamburguerC": 5,
    "tostadeatumC": 3,
    "tostadefrangoC": 2,
    "tostamistaC": 3,
    "cachorroC": 3,
    "bitoqueC": 4,
    "saladaC": 1,
    "aguaC": 3,
    "aguacomgasC": 5,
    "cafeC": 4,
    "descafeinadoC": 4,
    "cocacolaC": 2,
    "sevenupC": 3,
    "limonadaC": 5,
    "SumoDeLaranjaC": 3,
    "boloC": 3,
    "crepeC": 2,
    "geladoC": 3,
    "mousseC": 4,
    "frutaC": 4,
}

var Numclassificacoes = {
    "pistachiosC": 0,
    "amendoinsC": 0,
    "milhoC": 0,
    "tremocosC": 0,
    "azeitonasC": 0,
    "hamburguerC": 0,
    "tostadeatumC": 0,
    "tostadefrangoC": 0,
    "tostamistaC": 0,
    "cachorroC": 0,
    "bitoqueC": 0,
    "saladaC": 0,
    "aguaC": 0,
    "aguacomgasC": 0,
    "cafeC": 0,
    "descafeinadoC": 0,
    "cocacolaC": 0,
    "sevenupC": 0,
    "limonadaC": 0,
    "SumoDeLaranjaC": 0,
    "boloC": 0,
    "crepeC": 0,
    "geladoC": 0,
    "mousseC": 0,
    "frutaC": 0,
}

$(document).ready(function() {
    $("#content div").hide(); // Initially hide all content
    $("#tabs button:first").attr("id","current"); // Activate first tab
    $("#content div:nth-of-type(1)").fadeIn(); // Show first tab content
    
    $('#tabs button').click(function(e) {
        e.preventDefault();
        if ($(this).closest("button").attr("id") == "current"){ //detection for current tab
         return       
        }
        else{             
        $("#content div:not(#tabs)").hide(); //Hide all content
        $("#tabs button").attr("id",""); //Reset id's
        $(this).attr("id","current"); // Activate this
        $('#' + $(this).attr('name')).fadeIn(); // Show content for current tab
        }
    });
});

function showDivConfirmacao() {
    if(productList.length > 1){
        $("#left1 > *").fadeOut(500);
        $("#confirmacao").fadeIn(500);
    }
}

function showDivCancelar() {
    if(productList.length > 1){
        $("#left1 > *").fadeOut(500);
        $("#cancelar").fadeIn(500);
    }
}

function showDiv2() {
	$("#left1 > *").fadeOut(250);
	$("#empregado").fadeIn(250);
	$("#empregado, #left1 > *").delay(2500);
	$("#left1 #content, #left1 #tabs").fadeIn(1000);
	$("#empregado").fadeOut(250);
}

function changeImage(id1, id2) {
    $(id1).fadeOut(250);
    $(id2).fadeIn(250);
}

var orderTotal = 0; 
var accTotal = 0;
var completedOrdersVal = 0;
var productList = [];
var productsBought = [];
var productTemp = {pname:"", pid:"", pprice:"0", pquantity:"0"};

productList.push(productTemp);

function addItem(name, price, id){ 
    for(var i = 0; i<productList.length; i++){
        if(productList[i].pname === name){
            productList[i].pquantity = productList[i].pquantity + 1;
            productList[i].pprice = price * productList[i].pquantity;
            priceN = productList[i].pprice.toFixed(2);
            $("#"+id).html("<p>" + productList[i].pquantity + "x  " + name + ' - '+priceN +"€ "+ "</p><div><button id='sumB' onclick=" + "addQuant(" + id + ',' + price + ");></button> "+"<button id='minusB' onclick=" + "minusQuant(" + id + ',' + price + ");></button> "+"<button id='cancelB' onclick=" + "removeItem(" + id + ',' + price + ");></button></div>" + "</div>");
            orderTotal = orderTotal + price;
            orderTotalN = orderTotal.toFixed(2);
            text = orderTotalN + "€";
            priceN = price.toFixed(2);
            $("#total").text(text);
            return;
        }
    }
    var product = {pname:name, pid:id, pprice:price, pquantity:1};
    productList.push(product);
    orderTotal = orderTotal + price;
    orderTotalN = orderTotal.toFixed(2);
    text = orderTotalN + "€";
    priceN = price.toFixed(2);
    $("#currentOrder").append("<div id=" +id+"><p>" + product.pquantity + "x  " + name + ' - '+priceN +"€ "+ "</p><div><button id='sumB' onclick=" + "addQuant(" + id + ',' + price + ");></button> "+"<button id='minusB' onclick=" + "minusQuant(" + id + ',' + price + ");></button> "+"<button id='cancelB' onclick=" + "removeItem(" + id + ',' + price + ");></button></div>" + "</div>");
    $("#total").text(text);
};

function removeItem(id, price){

    var idde = id.id;
    var totalDiscount = 0;
    
    for(var i = 0; i<productList.length; i++){
        if(productList[i].pid === idde ){
            totalDiscount = productList[i].pprice;
            productList.splice(i, 1);
            
        }
    }
    
    orderTotal = orderTotal - totalDiscount;
    orderTotalN = orderTotal.toFixed(2);
    text = orderTotalN + "€";
    idd = '#' + id;
    $(id).remove();
    $("#total").text(text);
};

function addQuant(id, price){
    var idde = id.id;
    idd = "#" + idde;
    
    
    for(var i = 0; i<productList.length; i++){
        if(productList[i].pid === idde){
            productList[i].pquantity = productList[i].pquantity + 1;
            productList[i].pprice = price * productList[i].pquantity;
            priceN = productList[i].pprice.toFixed(2);
            name = productList[i].pname;
            $(idd).html("<p>" + productList[i].pquantity + "x  " + name + ' - '+priceN +"€ "+ "<div><button id='sumB' onclick=" + "addQuant(" + idde + ',' + price + ");></button> "+"<button id='minusB' onclick=" + "minusQuant(" + idde + ',' + price + ");></button> "+"<button id='cancelB' onclick=" + "removeItem(" + idde + ',' + price + ");></button></div>");
            orderTotal = orderTotal + price;
            orderTotalN = orderTotal.toFixed(2);
            text = orderTotalN + "€";
            priceN = price.toFixed(2);
            $("#total").text(text);
        }
    }
};

function minusQuant(id, price){
    var idde = id.id;
    idd = "#" + idde;

    for(var i = 0; i<productList.length; i++){
        if(productList[i].pid === idde){
            if(productList[i].pquantity == 1){
                removeItem(id, price);
                return;
            }else{
            productList[i].pquantity = productList[i].pquantity - 1;
            productList[i].pprice = price * productList[i].pquantity;
            priceN = productList[i].pprice.toFixed(2);
            name = productList[i].pname;
            $(idd).html("<p>" + productList[i].pquantity + "x  " + name + ' - '+priceN +"€ "+ "</p><div><button id='sumB' onclick=" + "addQuant(" + idde + ',' + price + ");></button> "+"<button id='minusB' onclick=" + "minusQuant(" + idde + ',' + price + ");></button> "+"<button id='cancelB' onclick=" + "removeItem(" + idde + ',' + price + ");></button></div>");
            orderTotal = orderTotal - price;
            orderTotalN = orderTotal.toFixed(2);
            text = orderTotalN + "€";
            priceN = price.toFixed(2);
            $("#total").text(text);
        }
        }
    }  
};

function addToAccTotal(){
    
    if(productList.length > 1){
    accTotal = accTotal + orderTotal;
    completedOrdersVal = completedOrdersVal + 1;
    addProductToClass();
    productsBought = productsBought.concat(productList);
    $("#completedOrders").append("<h3> Pedido nº" + completedOrdersVal + "</h3>");
    for(var i = 1; i<productList.length; i++){
        value = productList[i].pprice.toFixed(2);
        $("#completedOrders").append("<p>" + productList[i].pquantity + "x  " + productList[i].pname + ' - '+value +"€ "+ "</p>");
    }
    accTotalT = accTotal.toFixed(2);
    accTotalT = accTotalT + "€";
    $("#accTotalV").text(accTotalT);
    clearOrder();
    closeConfirmation();
    checkOrders();
	}
};

function checkOrders(){
    ("#completedOrders");
};

function apagarPedido1(){
    var legenda = "<div style=\" z-index: 999; position: absolute; margin-left: 26.5%; margin-top: 0%; background-color: white; font-size: 1.5em; font-weight: bold; padding: 5px;\">A sua classificação:</div>";
    if (justOnce == 0) {
        $("#info").hide();
        $("#classificarTotal").append(legenda);
        justOnce = 1;
    }
    $.each($("#currentOrder").children(), function (i, v) {
    	if(!$(".classificado#" + v.id).length) {
	        var htmls = "<div class=\"classificado\" id=\"" + v.id + "\"><img src=\"img/" + v.id + ".png\"><i class=\"fa\" data-value=\"1\" onclick=\"estrelasStuff(event)\">&#xf005</i><i class=\"fa\" data-value=\"2\" onclick=\"estrelasStuff(event)\">&#xf005</i><i class=\"fa\" data-value=\"3\" onclick=\"estrelasStuff(event)\">&#xf005</i><i class=\"fa\" data-value=\"4\" onclick=\"estrelasStuff(event)\">&#xf005</i><i class=\"fa\" data-value=\"5\" onclick=\"estrelasStuff(event)\">&#xf005</i><div class=\"number\"> Estrelas: 0 </div>";
	        $("#classificarTotal").append(htmls);
	    }
    });

    $("#BotaoC").show();

    productList.length = 0;
    productList.push(productTemp);
    $("#currentOrder").empty();
    
    orderTotal = 0;
    text = "0.00€"
    $("#total").text(text);
    retroceder1();
};

function apagarPedido2(){

    productList.length = 0;
    productList.push(productTemp);
    $("#currentOrder").empty();
    
    orderTotal = 0;
    text = "0.00€"
    $("#total").text(text);
    retroceder2();
};

function retroceder1(){
    $("#confirmar").fadeOut(500);
    $("#left1 #content, #left1 #tabs").fadeIn(500);
    return;
}

function retroceder2(){
    $("#cancelar").fadeOut(500);
    $("#left1 #content, #left1 #tabs").fadeIn(500);
    return;

}

function showDiv4(id) {
    $("#left1 > *").fadeOut(500);
    $(id).fadeIn(500);
}

function okClassify(){

    $("#classificarTotal").children().each(function (i, v) {
        if (i == 0) return;
        var id = $(v)[0].id;
        id = id + "C";
        var n = Number($(this).children(".number")[0].innerHTML.slice(11, 12));
        if (n != 0) {
            Numclassificacoes[id] = Numclassificacoes[id]+1;
            classificacoes[id] = ((classificacoes[id]*Numclassificacoes[id]) + n) / (Numclassificacoes[id]+1);
            $("a#" + id + " img:nth-of-type(2)").attr("src", "img/" + Math.round(classificacoes[id]) + "Star.png");
        }
    });
    console.log(classificacoes);
    console.log(Numclassificacoes);
    $("#classificarTotal").empty();
    $("#info").show();
    $("#BotaoC").hide();
    $("#classificar").fadeOut(500);
    $("#left1 #content, #left1 #tabs").show();
    justOnce = 0;
}

function closeIt(id) {
    $(id).hide();
    $("#left1 #content, #left1 #tabs").fadeIn(500);
};

function closeEmpregado() {
    $("#empregado").hide();
    $("#left1 #content, #left1 #tabs").show();
};

function estrelasStuff(evt) {
    var id = evt.currentTarget.parentNode.id;
    var theValue = Number(evt.currentTarget.dataset.value);
    $.each($(".classificado#" + id).children(), function (i, v) {
    	if (v.className == "fa" || v.className == "fa active") {
    		if (Number(v.dataset.value) <= theValue)
    			v.className = "fa active";
    		else
    			v.className = "fa";
    	}
    });
    
    $(".classificado#" + id + " div").html(" Estrelas: " + theValue + " ");
}