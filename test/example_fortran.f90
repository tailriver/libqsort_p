program main
    implicit none

    type point
        integer :: x, y
    end type point

    integer, allocatable :: array(:)
    type(point), allocatable :: vector(:)
    integer :: i

    allocate(array(6))
    array(1) = 5
    array(2) = 2
    array(3) = 3
    array(4) = 1
    array(5) = 7
    array(6) = 6

    allocate(vector(4))
    vector(1)%x = 0
    vector(1)%y = 1
    vector(2)%x = 0
    vector(2)%y = 0
    vector(3)%x = 1
    vector(3)%y = 1
    vector(4)%x = 1
    vector(4)%y = 0

    print *, "Before sort:"
    print *, array
    call QSORT_P(array, size(array), sizeof(array) / size(array), comp_int)
    print *, "After sort:"
    print *, array

    print *, "Before sort:"
    do i = 1, 4
        print *, vector(i)%x, vector(i)%y
    end do
    call QSORT_P(vector, size(vector), sizeof(vector) / size(vector), comp_point)
    print *, "After sort:"
    do i = 1, 4
        print *, vector(i)%x, vector(i)%y
    end do
    stop

    contains

    integer function comp_int(a, b)

        integer, intent(in) :: a, b

        if (a < b) then
            comp_int = -1
        else if (a == b) then
            comp_int = 0
        else
            comp_int = 1
        endif

    end function

    integer function comp_point(a, b)

        type(point), intent(in) :: a, b

        comp_point = comp_int(a%x, b%x)
        if (comp_point /= 0) then
            return
        end if

        comp_point = comp_int(a%y, b%y)

    end function

end program
