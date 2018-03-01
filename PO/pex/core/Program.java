package pex.core;

import java.io.BufferedWriter;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.OutputStreamWriter;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import java.util.*;
import pex.app.BadExpressionException;
import pex.app.BadPositionException;
import pex.parser.BadNumberException;
import pex.parser.BadSourceException;
import pex.parser.EndOfInputException;
import pex.parser.InvalidExpressionException;
import pex.parser.MissingClosingParenthesisException;
import pex.parser.NewParser;
import pex.parser.UnknownOperationException;
import java.io.Serializable;
import pex.core.Expression;
import pex.core.expression.Identifier;
import pex.core.expression.literal.Literal;
import pex.core.expression.literal.IntegerLiteral;
import pex.core.expression.compositeexpression.CompositeExpression;
import pex.app.BadExpressionException;

public class Program implements Serializable{

	private Interpreter _interp;
	private String _name;
	private ArrayList<Expression> _expressions;

	public Program(String name, Interpreter interp){
		_interp = interp;
		_name = name;
		_expressions = new ArrayList<Expression>();
	}

	public Interpreter getInterpreter() { 
		return _interp; 
	}
	
	public void setIdentifierValue(String name, Literal value) {
		_interp.setIdentifierValue(name, value);
	}
	
	public Literal getIdentifierValue(String id) {
		return _interp.getIdentifierValue(id);
	}

	public Program getProgram(String name) {
		return _interp.getProgram(name);
	}

	public ArrayList<Expression> getArguments(){
		return _expressions;
	}

	public Literal execute() throws BadExpressionException{
		Literal l = new IntegerLiteral(0);
		try{
			List<Expression> list = getArguments();
			for(Expression expression : list){
				l = expression.evaluate();
			}
			return l;
		} catch (BadExpressionException e){
			throw e;
		}
	}

	public String getName(){
		return _name;
	}

	public String getAsText(){
		return "" + getName();
	}

	public void set(ArrayList<Expression> expressions) {
		setExpressions(expressions);
	}

	public void setExpressions(ArrayList<Expression> expressions) {
		_expressions = expressions;
	}

	public int getNumberExpression(){
		return _expressions.size();
	}

	public ArrayList<Expression> getExpressions() {
		return _expressions;
	}

	public void addExpression(Expression expression) {
		_expressions.add(expression);
	}

	public String listExpressions(){
		String s = "";
		for(Expression expression : _expressions){
			s += expression.getAsText() + "\n";
		}
		return s;
	}

	public void writeToTextFile(String name) {
		 BufferedWriter writer;
		try {
			writer = new BufferedWriter(new OutputStreamWriter( new FileOutputStream(name), "utf-8"));
			writer.write(listExpressions());
			writer.close();
		} catch (UnsupportedEncodingException e) {
			e.printStackTrace();
		} catch (FileNotFoundException e) {
			e.printStackTrace();
		} catch (IOException e) {
			e.printStackTrace();
		}
	}

	public void addExpression(String expression, String idx ) throws BadPositionException, BadExpressionException{

		int index = Integer.parseInt(idx);
		Expression exp = null;
		NewParser parser = new NewParser();
		try {
			exp = parser.parseString(expression, this);		
		} catch (BadSourceException | BadNumberException | InvalidExpressionException
				| MissingClosingParenthesisException | UnknownOperationException | EndOfInputException e) {
			throw new pex.app.BadExpressionException(expression);
		}

		if (index > _expressions.size() || index < 0){
			throw new pex.app.BadPositionException(index);
		}

		else if (index == _expressions.size()){
			_expressions.add(exp);
		}
		else {
			_expressions.add(index, exp);
		}
	}

	public void replaceExpression(String expression, String idx ) throws BadPositionException, BadExpressionException{

		int index = Integer.parseInt(idx);
		Expression exp = null;
		NewParser parser = new NewParser();
		try {
			exp = parser.parseString(expression, this);		
		} catch (BadSourceException | BadNumberException | InvalidExpressionException
				| MissingClosingParenthesisException | UnknownOperationException | EndOfInputException e) {
			throw new pex.app.BadExpressionException(expression);
		}

		if (index >= _expressions.size() || index < 0){
			throw new pex.app.BadPositionException(index);
		}
		else {
			_expressions.remove(index);
			_expressions.add(index, exp);
		}
	}
}
