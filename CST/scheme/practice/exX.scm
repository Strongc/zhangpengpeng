(define pi
 (* 4 (atan 1.0))
 )

(define deg2rad
 (lambda (degree)
  (/ (* degree pi) 180)
 ))

(define (distance vx t)
 (* vx t))

(define duration
 (lambda (vy)
  (/ (* 2 vy) 9.8)
 ))

(define fly_distance
 (lambda (v theta)
  (distance 
   (* v (cos (deg2rad theta)))
   (duration (* v (sin (deg2rad theta))))
  )))

(define fly_distance2
 (lambda (v theta)
  (let ((r (/ (* 4 (atan 1.0) theta) 180)))
   (/ (* 2 v v (sin r) (cos r)) 9.8)
  )))

; new begin 
;

(define absolute
 (lambda (x)
  (if (>= x 0)
   (+ 0 x)
   (* -1 x)
  )))
(define absolute2
 (lambda (x)
  (* x
   (if (>= x 0)
	1
	-1
   )
  )))

(define pos_neg
 (lambda (x)
  (cond
   ((> x 0) "postive")
   ((< x 0) "negtive")
   (else "zero")
  )))
 
; new begin for looping
;

; recursive for looping
(define fact
 (lambda (n)
  (if (= 1 n)
   1
   (* n (fact (- n 1)))
  )))
; change to tail recursive
(define fact_tail
 (lambda (n)
  (fact_tail_r n 1)
 ))
(define fact_tail_r
 (lambda (co re)
  (if (= co 1)
   re
   (fact_tail_r (- co 1) (* co re))
  )))
; change to named let
(define fact_named_let
 (lambda (n)
  (let loop((co n) (re 1))
   (if (= 1 co)
	re
	(loop (- co 1) (* co re))
   ))))
; change to letrec
(define fact_letrec
 (lambda (n)
  (letrec ((iter
			(lambda (co re)
			 (if (= 1 co)
			  re
			  (iter (- co 1) (* co re))
			 ))))
   (iter n 1))))
; change to do
(define fact_do
 (lambda (n)
  (do
   ((co n (- co 1))
	(re 1 (* co re))
   )
   ((= 1 co) re)
   )))

; exercise

(define my_len
 (lambda (ls)
  (if (null? ls)
   0
   (+ 1 (my_len (cdr ls)))
  )))

(define sumof
 (lambda (ls)
  (sumof_r ls 0)))
(define sumof_r
 (lambda (ls re)
  (if (null? ls)
   re
   (sumof_r (cdr ls) (+ (car ls) re))
  )))
(define sumof_named_let
 (lambda (ls)
  (let loop((co ls) (re 0))
   (if (null? co)
	re
	(loop (cdr co) (+ (car co) re))
   ))))
(define sumof_letrec
 (lambda (ls)
  (letrec ((iter
			(lambda (co re)
			 (if (null? co)
			  re
			  (iter (cdr co) (+ (car co) re))
			 ))))
   (iter ls 0))))
(define sumof_do
 (lambda (ls)
  (do 
   ((co ls (cdr co))
	(re 0 (+ (car co) re)))
   ((null? co) re)
  )))

(define posof
 (lambda (ls x)
  (posof_r ls x 0)))
(define posof_r
 (lambda (ls x re)
  (cond
   ((null? ls) #f)
   ((eqv? x (car ls)) re)
   (else (posof_r (cdr ls) x (+ 1 re)))
  )))
(define posof_letrec
 (lambda (ls x)
  (letrec ((iter
			(lambda (ls_r res)
			 (cond
			  ((null? ls_r) #f)
			  ((eqv? x (car ls_r)) res)
			  (else (iter (cdr ls_r) (+ 1 res)))
			 ))))
   (iter ls 0))))
(define posof_named_let
 (lambda (ls x)
  (let loop((ls_r ls) (res 0))
   (cond
	((null? ls_r) #f)
	((eqv? x (car ls_r)) res)
	(else (loop (cdr ls_r) (+ 1 res)))
   ))))

(define removeone
 (lambda (ls x)
  (if (null? ls)
   '()
   (let ((h (car ls)))
	((if (eqv? h x)
	  (lambda (y) y)
	  (lambda (y) (cons h y)))
	 (removeone (cdr ls) x))))))
(define removeone_letrec
 (lambda (ls x)
  (letrec ((iter
			(lambda (ls_r x_r res)
			 (if (null? ls_r)
			  res
			  (let ((h (car ls_r)))
			   (if (eqv? h x_r)
				 (iter (cdr ls_r) x_r res)
				 (iter (cdr ls_r) x_r (cons res h))
			   ))))))
   (iter ls x '()))))
(define removeone_letrec2
 (lambda (ls x)
  (letrec ((iter
			(lambda (ls_r res)
			 (if (null? ls_r)
			  res
			  (let ((h (car ls_r)) (t (cdr ls_r)))
			   (if (eqv? h x)
				(iter t res)
				(iter t (cons res h))
			   ))))))
   (iter ls '()))))


; new begin for higher order functions
;

(define double_list
 (lambda (ls)
  (map
   (lambda (x)
	(* 2 x))
   ls)))
(define sub_list
 (lambda (ls1 ls2)
  (map - ls1 ls2)))

(define sum_list
 (lambda (ls)
  (begin
   (define sum 0)
   (for-each
	(lambda (x) (set! sum (+ sum x)))
	ls)
   sum)))

(define keep_even
 (lambda (ls)
  (keep-matching-items ls even?)))
(define delete_from_10_to_100
 (lambda (ls)
  (delete-matching-items ls 
   (lambda (x) (<= 10 x 100))
  )))

(define sqrt_sum_sq
 (lambda (ls)
  (sqrt
   (reduce +
	0 
	(map
	 (lambda (x) (* x x))
	 ls)))
 ))

(define sort_by_mod
 (lambda (ls)
  (sort ls
   (lambda (x y)
	(< (modulo x 100) (modulo y 100))))
 ))

; new begin to read and write file
;

(define read_file_print
 (lambda (file_name)
  (let
   ((p (open-input-file file_name)))
   (let
	loop((ls '()) (c (read-char p)))
	(if (eof-object? c)
	 (begin
	  (close-input-port p)
	  (list->string ls ));(reverse ls)))
	 (loop (cons c ls) (read-char p)))))))

(define read_file_print2
 (lambda (file_name)
  (call-with-input-file file_name
   (lambda (p)
	(let
	 loop((ls '()) (c (read-char p)))
	 (if (eof-object? c)
	  (begin
	   (close-input-port p)
	   (list->string (reverse ls)))
	  (loop (cons c ls) (read-char p))))))))

(define read_file_print3
 (lambda (file_name)
  (with-input-from-file file_name
   (lambda ()
	(let
	 loop((ls '()) (c (read-char)))
	 (if (eof-object? c)
	  (list->string (reverse ls))
	  (loop (cons c ls) (read-char))))))))

(define s-read
 (lambda (file_name)
  (with-input-from-file file_name
   (lambda ()
	(let 
	 loop((ls '()) (s (read)))
	 (if (eof-object? s)
	  (reverse ls)
	  (loop (cons s ls) (read))))))))

(define my_copy_file
 (lambda (file_from file_to)
  (let ((pfr (open-input-file file_from))
		(pto (open-output-file file_to)))
   (let loop((c (read-char pfr)))
	(if (eof-object? c)
	 (begin
	  (close-input-port pfr)
	  (close-output-port pto))
	 (begin
	  (write-char c pto)
	  (loop (read-char pfr)))))
  )))


; new begin for defining syntax
;

(define-syntax nil!
 (syntax-rules ()
  ((_ x)
   (set! x '()))))
(define f-nil
 (lambda (x)
  (set! x '())))

(define-syntax when
 (syntax-rules ()
  ((_ pred b1 ...)
   (if pred (begin b1 ...)))))
(define-syntax while
 (syntax-rules ()
  ((_ pred b1 ...)
   (let loop () (when pred b1 ... (loop))))))
(define-syntax for
 (syntax-rules ()
  ((_ (x from to) b1 ...)
   (let loop((x from))
	(when (< x to)
	 b1 ...
	 (loop (1+ x)))))))

(define-syntax my-and
 (syntax-rules (al-true)
  ((_ al-true e1 ...) #t)		; always true
  ((_ al-false) #f)
  ((_) #t)
  ((_ e) e)
  ((_ e1 e2 ...)
   (if e1 (my-and e2 ...) #f))
  ))

; new begin for continuation
;
(define call/cc call-with-current-continuation)
(define (find-leaf obj tree)
 (call/cc
  (lambda (cc)
   (letrec ((iter
			 (lambda (tree)
			  (cond
			   ((null? tree) #f)
			   ((pair? tree)
				(iter (car tree))
				(iter (cdr tree)))
			   (else
				(if (eqv? obj tree)
				 (cc obj)))))))
	(iter tree)))))

(define (leaf-generator tree)
  (let ((return '()))                                                        ; 1
	(letrec ((continue                                                      ; 2
			   (lambda ()
				 (let loop ((tree tree))                                     ; 3
				   (cond                                                     ; 4
					 ((null? tree) 'skip)                                     ; 5
					 ((pair? tree) (loop (car tree)) (loop (cdr tree)))       ; 6
					 (else                                                    ; 7
					   (call/cc (lambda (lap-to-go)                            ; 8
								  (set! continue (lambda () (lap-to-go 'restart)))    ; 9
								  (return tree))))))                      ;10
				 (return '()))))                                         ;11
	  (lambda ()                                                     ;12
		(call/cc (lambda (where-to-go)                               ;13
				   (set! return where-to-go)                         ;14
				   (continue)))))))

	
