(define goal
 (lambda (lisp_scheme)
  (display '("Learn Functional Programming"))))

(Calculator
  (+ - * / quotient modulo sqrt)
  (sin cos tan asin acos atan exp log expt)
 )

(Cons_Cells_and_Lists
  ; Scheme manipulates all the data by their addresses
  (1 2 3) "is" (cons 1 (cons 2 (cons 3 '())))
  ; cons cells storage two addresses which can be different kinds of data
  ; Atoms: Numbers, characters and etc.;
  (car cdr)
  (list)
 )

(Quote_
  (quote (+ 2 9))
  '(+ 2 9) ;protect tokens from evaluation
  ; Scheme has two kinds of operators: functions and special forms.
  ; Functions evaluate all the arguments to return value, while Special forms not.
  ; quote, lambda, define, if, set!, etc. are special forms.
 )

(define define_symbol
 (lambda ()		; define fun's content by using lambda
  ;use define to bind a global symbol to a value including a function
  (define symbol value)
  (lambda (args) (ops))
  ((lambda (args) (ops)) values)
  (define (fun_name fun_args) (fun_ops)) ;a short form for fun definitions
 ))

(begin <sequence>)

(if predicate then_value else_value)
(cond (predicate_n clauses_n) (else clauses_else))

(let binds body)       (let ((x 1) (y 2)) (+ x y))
(let* binds_ex body)   (let* ((x 1) (y (+ x 1))) (+ x y))

; Recursion is a usual way for looping/repetition.
(define FUN_NAME
 (lambda (conditions)
  (if (boundary conditions)
   "stop with value"
   (process by calling FUN_NAME itself with next conditions)
 )))
; tail recursive. And treat results as one param
(define FUN_NAME
 (lambda (conditions)
  (FUN_NAME_R conditions init_results)
 ))
(define FUN_NAME_R
 (lambda (co re)
  (if (boundary co)
   (return re)
   (FUN_NAME_R (next co) (next re))
  )))
; letrec is a conventional way to define local-fun
  (letrec ((iter
			(lambda (co re)
			 (if (boundary co)
			  (return re)
			  (iter (next co) (next re))
			 ))))
   (iter init_co init_re))
; named let is a conventional way to loop
  (let loop((co init_co) (re init_re))
   (if (boundary co)
	(return re)
	(loop (next co) (next re))
   ))
; do is changing variable until boundary
(do ((co init_co next_co) (re init_re next_re)) ((boundary co) re))

(higher_order_functions functions lists)
(map for-each keep-matching-items delete-matching-items reduce sort quick_sort apply)

(open-input-file filename)	; open a file and return a port
(open-output-file filename)
(read-char port)	; return a character, use let to assign to a symbol
(read port)			; reads a S-expression from the port
(eof-object? c)		; check end
(write obj port)
(display obj port)
(newline port)
(write-char char port)
(close-input-port port)		; close file
(close-output-port port)
(call-with-input-file filename procedure)  ; procedure takes input port as an arg.
(call-with-output-file filename procedure)
(with-input-from-file filename procedure)  ; same as above but procedure hasn't this arg.
(with-output-to-file filename procedure)

(set! set-car! set-cdr!)
; we can make procedures with internal status by using the lexical closure (static scope).

;user_defined_syntax is called macro.
(define-syntax my_syntax
 (syntax-rules (reserved_words)
  ((_ param) do_sth)			; is able to edit param while fun can't
  ((_ param_head ...) do_sth)	; arbitrary numbers of param by using ...
  ((_ another_format) do_sth)	; define several patterns
  ((_ param) do_sth_by_calling_itself)	; recursive definition
  ((_ reserved_words) do_sth)	; reserved_word won't be transformed
  ((_ reserved_words param_head ...) do_sth)
 ))
(define local syntax using let-syntax and letrec-syntax)
 
; Continuation_Passing_Style pass function as param which can change more flexible.
(define (kfact n k)
 (if (= n 1)
  (k 1)
  (kfact (- n 1) (lambda (x) (k (* n x))))))
(kfact 4 (lambda (x) x))
k(x) => k(4x) => k(4(3x)) => k(4(3(2x))) => k(4(3(2(1)))) = k(24)	; change function continuously by changing its param 
(define call/cc call-with-current-continuation)
(fun_cur_conti other_param (call/cc (lambda (k) (do_sth_return_as_PARAM_Or_(k_PARAM)_directly))))
k is equal to (fun_cur_conti other_param PARAM) and return;
; escape from a process and throw values using call/cc

