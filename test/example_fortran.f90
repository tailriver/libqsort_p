program main
    implicit none

    integer :: array(6)

    array(1) = 5
    array(2) = 2
    array(3) = 3
    array(4) = 1
    array(5) = 7
    array(6) = 6

    print *, array
    call QSORT_P(array, 6, 4, comp_int)
    print *, array
    stop

    contains

    integer function comp_int(a, b)

        integer, intent(in) :: a, b

        if (a < b) then
            comp_int = 1
        else if (a == b) then
            comp_int = 0
        else
            comp_int = -1
        endif

    end function

end program
