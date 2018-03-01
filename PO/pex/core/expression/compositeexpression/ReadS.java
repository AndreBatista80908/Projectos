package pex.core.expression.compositeexpression;

import java.util.*;
import pex.AppIO;
import pex.core.Expression;
import pex.core.expression.literal.Literal;
import pex.core.expression.literal.StringLiteral;
import pex.core.expression.compositeexpression.CompositeExpression;
import pex.app.BadExpressionException;

public class ReadS extends CompositeExpression{

	private AppIO _io;

	public ReadS(AppIO io){
		_io = io;
	}

	public String getAsText(){
		return "(" + getName() + ")";
	}

	public String getName(){
		return "reads";
	}

	public Literal evaluate() throws BadExpressionException {
		try{
        	return new StringLiteral(_io.readString());
        } catch (ClassCastException cast){
			throw new BadExpressionException(this.getAsText());
		}
	}
}
