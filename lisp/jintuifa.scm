(define (jintui f x h t)
  (cond ((> (f (+ x h)) (f x))
         (iter f x (- 0 h) t))
        (else
         (iter f x h t))))

(define (iter f x h t)
  (cond ((< (f (+ x h)) (f x))
         (iter f (+ x h) (* t h) t))
        (else
         (cons (- x (/ h t))  (+ x h)))))

(define (sq x)
  (* x x))

(define prints (lambda args (for-each display args)))
(define (pcons c)
  (prints "[")
  (cond ((> (car c) (cdr c))
         (prints (car c) "," (cdr c)))
        (else
         (prints (cdr c) "," (car c))))
  (prints "]")
  (newline))
