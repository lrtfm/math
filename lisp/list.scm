(define nil '())
(define (list-ref items n)
  (if (= n 0)
    (car items)
    (list-ref (cdr items) (- n 1))))

;;; (define (length items)
;;;   (if (null? items)
;;;     0
;;;     (+ 1 (length (cdr items)))))

(define (length items)
  (define (length-iter a count)
    (if (null? a)
      count
      (length-iter (cdr a) (+ 1 count))))
  (length-iter items 0))

(define (append list1 list2)
  (if (null? list1)
    list2
    (cons (car list1) (append (cdr list1) list2))))

;;; this why not work
(define (reverse items)
  (if (null? items)
    nil
    (append (reverse (cdr items)) (list (car items)))))
;;;(define (reverse items)
;;;  (cond ((null? items) nil)
;;;        ((not (pair? items)) (list items))
;;;        (else (append (reverse (cdr items)) (list (car items))))))

