package pex.core.expression.compositeexpression.variadicexpression;

import java.util.*;
import pex.AppIO;
import pex.core.Expression;
import pex.core.expression.literal.Literal;
import pex.core.expression.literal.IntegerLiteral;
import pex.app.BadExpressionException;

public class Seq extends VariadicExpression{

	public Seq(ArrayList<Expression> e){
		setArguments(e);
	}
	
	public String getName(){
		return "seq";
	}

	public Literal evaluate() throws BadExpressionException {
		try{
			Literal literal = null;
			List<Expression> list = getArguments();
			for(Expression expression : list){
				literal = expression.evaluate();
			}
			return literal;
		} catch (ClassCastException cast){
			throw new BadExpressionException(this.getAsText());
		}
	}
}
