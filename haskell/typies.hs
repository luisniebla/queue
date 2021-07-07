
import qualified Data.Map as Map

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


-- Derived Instances
data Animal = Animal { name :: String, animalAge ::Int } deriving (Eq)
areSameAnimal = Animal {name = "Cat", animalAge = 2} == Animal {name = "Cat", animalAge = 3}

-- You can now use Animal in any function that constrains on Eq
myPets = [Animal {name = "Cat", animalAge = 2}, Animal {name = "Cat", animalAge = 3}]
isMyPet = Animal {name = "Cat", animalAge = 2} `elem` myPets

-- You can dervive multiple instances
data Cat = Cat { catName :: String, catAge :: Int } deriving (Eq, Show, Read)
myCat = Cat { catName = "Juju", catAge = 2 }

-- The Read instance takes in a string and returns a type
-- Note: You need to do the :: casting or haskell will complain when printing
herCat = read "Cat {catName = \"Doggo\", catAge=3}" :: Cat

data Day = Monday | Tuesday | Wednesday | Thursday | Friday | Saturday | Sunday deriving (Eq, Ord, Show, Read, Bounded, Enum)
currentDay = read "Tuesday" :: Day
isBeforeFriday = currentDay < Friday
maxDay = maxBound :: Day
dayAfterToday = succ currentDay


-- Type Synonyms. Note types must start with capital letter
type StringSynonym = [Char]
type PhoneNumber = String
type Name = String
type PhoneMap = [(Name, PhoneNumber)]
phoneBook = [("Luis", "602"), ("Niebla", "555")]

-- Parameterized type synonyms
type AssocList k v = [(k,v)]
type IntMap = Map.Map Int

-- Using parameterized type snonyms
test = [(1,2),(3,5)] :: AssocList Int Int


-- Recursive Data Structures
t1 = [5] == 5:[]
t2 = [4,5] == 4:(5:[])
-- A list is either an empty list, or a head with a list at the end
data List a = Empty | Cons a (List a) deriving (Show, Read, Eq, Ord)
-- Cons is another keyword for ":"
t3 = 5 `Cons` Empty
t4 = 4 `Cons` (5 `Cons` Empty)

-- infixr defines the right associative operation
infixr 5 :-: 
data FixityList a = EmptyFixity | a :-: (FixityList a) deriving (Show, Read, Eq, Ord)
t5 = 3 :-: 4 :-: 5 :-: EmptyFixity  

-- redefenition of the adding of two lists using custom recursive structure
infixr 5 .++
EmptyFixity  .++ ys = ys
(x :-: xs) .++ ys = x :-: (xs .++ ys)  

-- Binary search tree
data Tree a = EmptyTree | Node a (Tree a) (Tree a) deriving (Show, Read, Eq)
-- Take a tree, and an element and inserts an element to left or right depending on comparison
treeInsert x EmptyTree = Node x EmptyTree EmptyTree -- A node that has something and then two empty sub-trees
treeInsert x (Node a left right)
    | x == a = Node x left right
    | x < a  = Node a (treeInsert x left) right
    | x > a  = Node a left (treeInsert x right)
exampleTree = foldr treeInsert EmptyTree [4,2,1,5,2,15]

-- Check if element is in the tree
treeElem x EmptyTree = Prelude.False
treeElem x (Node a left right)
    | x == a = Prelude.True
    | x < a  = treeElem x left
    | x > a  = treeElem x right



-- Typeclasses 102
data TrafficLight = Red | Yellow | Green
-- the instance keyword defines types instances of typeclasses
instance Eq TrafficLight where
    Red == Red = Prelude.True
    Green == Green = Prelude.True
    Yellow == Yellow = Prelude.True
    _ == _ = Prelude.False

instance Show TrafficLight where
    show Red = "Stop"
    show Yellow = "Slow Down"
    show Green = "Go"


-- Functor typelcass
class Functor f where
    fmap :: (a -> b) -> f a -> f b
-- fmap takes a fucntion from one type to another and a functor applied with one type and returns a functor applied with another type
instance Main.Functor [] where
    fmap = map
t6 = Main.fmap (*2) [1..3]

main = do
    print someRect
    print me
    print newType
    print myArrow
    print arrowSum
    print areSameAnimal
    print isMyPet
    print ("My Cat is " Prelude.++ show myCat)
    print ("Her cat is" Prelude.++ show herCat)
    print (show Wednesday)
    print maxDay
    print dayAfterToday
    print t3
    print t4
    print t5
    print exampleTree
    print (treeElem 15 exampleTree)