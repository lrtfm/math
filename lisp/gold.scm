(define (gold-section-method f a b e)
  (let ((l (+ a (* 0.382 (- b a))))
        (r (+ a (* 0.618 (- b a)))))
    (iter f a b l r e) 
    )
  )

(define (iter f a b l r e)
  (cond ((> (f l) (f r))
          (if (> (- b l) e)
            (iter f l b r (+ l (* 0.618 (- b l))) e)
            r))
         (else
           (if (> (- r a) e)
             (iter f a r (+ a (* 0.382 (- r a))) l e)
             l))))

;;; Test 
(define (sq x)
  (* x x))

;;; Expect 0
(gold-section-method sq -1 1 0.001)
(gold-section-method sq -3 1 0.001)

