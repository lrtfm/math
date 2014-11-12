(define tolerance 0.00001)

(define  (fixed-point f first-guess)
  (define (close-enough? v1 v2)
    (< (abs (- v1 v2)) tolerance))
  (define (try guess)
    (let ((next (f guess)))
      (if (close-enough? guess next)
        next
        (try next))))
  (try first-guess))

(define (deriv g)
  (lambda (x)
    (/ (- (g (+ x dx)) (g x))
       dx)))

(define (cubic a b c)
  (lambda (y)
    (+ (* x x x)
       (* a x x)
       (* b x)
       c)))

(define (compose f g)
  (lambda (x)
    (f (g x))))

(define (fun1 x)
  (* x x))
(define (fun2 x)
  (+ x 1))

(define (repeated f n)
  (repe-iter f f n))

(define (repe-iter g f counter )
  (if (< counter 2)
    g
    (repe-iter (compose f g) f (- counter 1))))

(+ 3 3)
(define zero (lambda (f)  (lambda (x) x)))

(define (add-1 n)
  (lambda (f)  (lambda (x)  (f ((n f) x)))))
(cons 1
      (cons 2
            (cons 3
                  (cons 4 nil))))
(cons 1 nil)
