package pex.core.expression.literal;

import java.util.*;
import pex.core.Expression;

public abstract class Literal extends Expression{
	
	public abstract String stringValue();
	
	public Literal evaluate(){
		return this;
	}
}
