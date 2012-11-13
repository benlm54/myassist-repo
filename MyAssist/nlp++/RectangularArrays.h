//----------------------------------------------------------------------------------------
//	Copyright © 2007 - 2012 Tangible Software Solutions Inc.
//	This class can be used by anyone provided that the copyright notice remains intact.
//
//	This class provides the logic to simulate Java rectangular arrays, which are jagged
//	arrays with inner arrays of the same length.
//----------------------------------------------------------------------------------------
public class RectangularArrays
{
public:
    static int*** ReturnRectangularIntArray(int Size1, int Size2, int Size3)
    {
        int*** Array = new int**[Size1];
        for (int Array1 = 0; Array1 < Size1; Array1++)
        {
            Array[Array1] = new int*[Size2];
            for (int Array2 = 0; Array2 < Size2; Array2++)
            {
                Array[Array1][Array2] = new int[Size3];
            }
        }
        return Array;
    }
};