package pex.core.expression.compositeexpression.variadicexpression;

import pex.app.App;
import java.util.*;
import pex.AppIO;
import pex.core.Expression;
import pex.core.expression.literal.Literal;
import pex.core.expression.literal.IntegerLiteral;
import pex.app.BadExpressionException;

public class Print extends VariadicExpression{
	
	private AppIO _io;
	
	public Print(ArrayList<Expression> e, AppIO io){
		setArguments(e);
		_io = io;
	}

	public String getName(){
		return "print";
	}

	public Literal evaluate() throws BadExpressionException {
		try{
			String text = ""; 
			Literal literal = new IntegerLiteral(0);
			List<Expression> list = getArguments();
			for(Expression expression : list){
				literal = expression.evaluate();
				text += literal.stringValue();
			}
			_io.println(text);
			return literal;
		} catch (ClassCastException cast){
			throw new BadExpressionException(this.getAsText());
		}
	}
}