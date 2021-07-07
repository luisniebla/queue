-- Type Classes
data Bool = False | True
data Point = Point Float Float deriving (Show)

data Shape = Circle Point Float | Rectangle Point Point deriving (Show)

-- Here we name the value constructor same as the data type for convenience


surface (Circle _ r) = pi * r ^ 2
surface (Rectangle (Point x1 y1) (Point x2 y2)) = (abs $ x2 - x1) * (abs $ y2 - y1)

-- Value constructors take some value and produce a new value
someRect = Rectangle (Point 60.0 30.0) (Point 90.1 99.2)


-- Record Syntax

data Person = Person { firstName :: String
                        , lastName :: String
                        , age :: Int
                        , height :: Float
                        , phoneNumber :: String
                        , flavor :: String
                        } deriving (Show)

me = Person {firstName="Luis", lastName="Niebla", age=26, height=5.9, phoneNumber="602", flavor="blue"}


-- Type Parameters take types as parameters and produce new types
data Maybe a = Nothing | Just a
-- The type parameter is "a"
-- The type constructor is "Maybe"
-- Maybe produces a type of Maybe Int, Maybe Car, Maybe String, etc...

data MaybeShow a = NothingShow | JustShow a deriving (Show)
-- We define this show type so we can print the type and understand how it works
newType = JustShow "Me" -- Produces new type JustShow "Me"


-- Operations on type parameters
data Vector a = Vector a a a deriving (Show)
myArrow = Vector 1 2 3
(Vector i j k) `addVectors` (Vector l m n) = Vector (i+l) (j+m) (k+n)
secondArrow = Vector 4 5 6
arrowSum = myArrow `addVectors` secondArrow


main = do
    print someRect
    print me
    print newType
    print myArrow
    print arrowSum
