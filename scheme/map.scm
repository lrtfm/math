(define nil '())
;;; (define (scale-list items factor)
;;;   (if (null? items)
;;;     nil
;;;     (cons (* (car items) factor)
;;;           (scale-list (cdr items) factor))))
;;; 
(define (map proc items)
  (if (null? items)
    nil
    (cons (proc (car items))
          (map proc (cdr items)))))

(define (scale-list items factor)
  (map (lambda (x) (* x factor)) items))

(define (for-each proc items)
  (if (null? items)
    (newline)
    (and (proc (car items))
         (for-each proc (cdr items)))))

;;; (define (for-each proc items)
;;;   (if (not (null? items))
;;;     (and (proc (car items))
;;;          (for-each proc (cdr items)))))
