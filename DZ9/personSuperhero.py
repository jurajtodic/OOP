class Person:
    __slots__ : ["name", "age"]
    
    def __init__ (self, name, age):
        self.name = name
        self.age = age
    
    def walk (self):
        print("{} ({}) walks".format(self.name, self.age))
        
    def say(self, message):
        print("{} says: {}".format(self.name, message))
        
class Superhero(Person):
    __slots__ : ["secret_identity"]
    
    #def __init__ (self, name, age, secret_identity):
        #self.name = name
        #self.age = age
        #self.secret_identity = secret_identity
    
    def __init__(self, name, age, secret_identity):
        super(Superhero, self).__init__(name, age)
        self.secret_identity = secret_identity
        
    def fly(self):
        print("{} ({}) flies".format(self.name, self.age))
        
    def use_super_sight(self):
        print("{} (aka {}) uses super sight".format(self.name, self.secret_identity))
        
    def walk (self, use_power):
        if use_power == True:
            print("{} ({}) uses extra-speed running".format(self.name, self.age))
        else:
            #print("{} ({}) walks".format(self.name, self.age))
            super(Superhero, self).walk()
        
    
if __name__ == "__main__":
    
    Osoba1 = Person("Mike", 31)
    Osoba1.walk()
    Osoba1.say("Hello World")      
    
    print("\n\n")
    
    Osoba2 = Superhero("Peter", 21, "Spiderman")
    Osoba2.fly()
    Osoba2.use_super_sight()
    
    Osoba2.walk(True)
    Osoba2.walk(False)
    
    
    