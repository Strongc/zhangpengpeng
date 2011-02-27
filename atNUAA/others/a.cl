(defun append2 (x y)
 (cond ((eq x nil) y) (t (cons (car x) (append (cdr x)))))
 )
(append '(1 2) '(3 4))
