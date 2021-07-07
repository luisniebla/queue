
data Bool = False | True

data Point = Point Float Float deriving (Show)
-- Circle value constructor has 3 fields which take floats

data Shape = Circle Point Float | Rectangle Point Point deriving (Show)

-- Here we name the valuec onstructor same as the data type for convenience

-- data Shape = Circle Point Float | Rectangle Point Point deriving (Show)

surface (Circle _ r) = pi * r ^ 2
surface (Rectangle (Point x1 y1) (Point x2 y2)) = (abs $ x2 - x1) * (abs $ y2 - y1)

data Person = Person { firstName :: String
                        , lastName :: String
                        , age :: Int
                        , height :: Float
                        , phoneNUmber :: String
                        , flavor :: String
                        } deriving (Show)

main = print 1