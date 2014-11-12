(load "map.scm")
(load "list.scm")

(define x (list (list 1 2) (list 3 4)))

(length x)
(define (count-leaves x)
  (cond ((null? x) 0)
        ((not (pair? x)) 1)
        (else (+ (count-leaves (car x))
                 (count-leaves (cdr x))))))

(define (deep-reverse x)
  (if (pair? x) 
    ;;; (list (deep-reverse (cdr x)) (deep-reverse (car x))) 
    (reverse (deep-reverse (car x)) (deep-reverse (cdr x))) 
    x))

(define (deep-reverse L) 
  (if (pair? L) 
    (reverse (map deep-reverse L))
    L))
