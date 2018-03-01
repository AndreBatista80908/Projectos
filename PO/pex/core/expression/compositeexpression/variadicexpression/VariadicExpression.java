package pex.core.expression.compositeexpression.variadicexpression;

import java.util.*;
import pex.core.Expression;
import pex.core.expression.literal.IntegerLiteral;
import pex.core.expression.compositeexpression.CompositeExpression;

public abstract class VariadicExpression extends CompositeExpression{

	ArrayList<Expression> _expression;

	public ArrayList<Expression> getArguments(){
		return _expression;
	}

	public void setArguments(ArrayList<Expression> expression){
		_expression = expression;
	}

	public void set(ArrayList<Expression> list){
		_expression = list;
	}

	public void add(int idx, Expression expression){
		_expression.add(idx, expression);
	}

	public void replace(int idx, Expression expression){
		_expression.set(idx, expression);
	}

	public String getAsText(){
		String text = ""; 
		List<Expression> list = getArguments();
		for(Expression expression : list){
			text = text + " " + expression.getAsText();
		}
		return "("+ getName() + text + ")";
	}
}
