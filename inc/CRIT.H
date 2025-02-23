/* "crit" macros are originally from STD.H */

/* This file must be explicitly included in any files wishing to */
/* declare "critical" and "normal" sections of code.             */

/* Enable exactly one of the following:                                    */
   #define CRITOPT0                /* no criticality provisions            */
/* #define CRITOPT1 */             /* cli/sti w/IMR masking                */
/* #define CRITOPT2 */             /* CRITOPT1 with caller sti (see note)  */
/* #define CRITOPT3 */             /* IMR masks IRQ1-7 only (see note)     */

/* Note:  CRITOPT2 has better profiling characteristics than CRITOPT1.     */
/* In CRIOPT1, there is one single sti in os_normal() that gets reported   */
/* for *all* critical code.  In CRITOPT2, those sti's are spread out to    */
/* map all outermost critical/normal pairs.  In CRITOPT3, timer interrupts */
/* stay enabled in critical sections, allowing even better profiling.      */

#define use_critical     int _savpri

#ifdef CRITOPT0          /* No special handling of critical sections       */
#define critical         (_savpri = 0)
#define normal           ((void)_savpri)
#endif

#ifdef CRITOPT1          /* Interrupts disabled, IMR masked                */
#define critical         (_savpri = os_critical())
#define normal           (os_normal(_savpri))
#endif

#ifdef CRITOPT2          /* Caller enables interrupts -- better profiling  */
#define critical         (_savpri = os_critical())
#define normal           if (os_qnormal(_savpri)) asm sti
#pragma inline
#endif

#ifdef CRITOPT3          /* Timer interrupt stays enabled -- best profiling*/
#define critical         (_savpri = os_critical())
#define normal           (os_normal(_savpri))
#endif                   /* (distinctions from CRITOPT1 are in GALHPAC.C)  */


                              /* Clone of CRITOPT1 that is always defined  */
#define real_critical         (_savpri = os_critical())
#define real_normal           (os_normal(_savpri))

int os_critical(void);
void os_normal(int priority);
int os_qnormal(int priority);

