# Errors & Warnings

```
ERROR
	Conflict variables	-- Variables have the same name in the same scope
	Conflict function(s)	-- Functions or functions and variable have the same name even in different scope
	Wrong assignment	-- Assigning to invalid integer variable, or even not-a-variable
	Wrong parameter(s)	-- Assigning invalid actual parameters to the function call
	Wrong expression	-- Using arithmetic expression in condition
	Undefined variable  -- Using an undefined variable
	Undefined function  -- Using an undefined function (the function may be declared)

WARNING	
	Mixed expression	-- Mix the logical and arithmatic expressions together
	No return		-- The last statement in the function body is not a return
	Function declarition in function body	-- Declare a function inside another function body, which is allowed, but highly unrecommended!
```

## Errors

Conflict variables

![conflict_variables](/errors/conflict_variables.png)

Notice that variables in different scopes with the same name are allowed.

![duplicate_variables_in_different_scope](/errors/duplicate_variables_in_different_scope.png)

Conflict function(s)

![conflict_functions](/errors/conflict_functions.png)

Wrong assignment

![wrong_assignment](/errors/wrong_assignment.png)

Wrong parameter(s)

![wrong_actual_parameters](/errors/wrong_actual_parameters.png)

Wrong expression

![wrong_expression](/errors/wrong_condition.png)

Undefined variable

![undefined_variable](/errors/undefined_variable.png)

Undefined function

![undefined_function](/errors/undefined_function.png)

## Warnings

Mixed expressions

![mixed_expressions](/warnings/mixed_expressions.png)

No return

![no_return](/warnings/no_return.png)

Function declaration in function body

![function_declaration_in_function_body](/warnings/declaration_function_inside_function_body.png)