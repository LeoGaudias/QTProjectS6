#------------------------------------------------------------
#        Script MySQL.
#------------------------------------------------------------


#------------------------------------------------------------
# Table: Personne
#------------------------------------------------------------

CREATE TABLE Personne(
        Id          int (11) Auto_increment  NOT NULL ,
        DateNaiss   Date NOT NULL ,
        Sexe  		Boolean NOT NULL ,
        Etat_civil  Varchar (25) NOT NULL ,
        Nb_personne Int NOT NULL,
        Nb_enfant   Int NOT NULL ,
        Nb_Animaux  Int NOT NULL ,
        Revenu  	Int NOT NULL ,
        admin		Boolean NOT NULL DEFAULT 0,
        PRIMARY KEY (Id )
)ENGINE=InnoDB;


#------------------------------------------------------------
# Table: Yaourt
#------------------------------------------------------------

CREATE TABLE Yaourt(
        IdY    int (11) Auto_increment  NOT NULL ,
        Marque Varchar (50) NOT NULL ,
        Nom    Varchar (50) NOT NULL ,
        Type   Varchar (50) ,
        Gout   Varchar (50) NOT NULL ,
        PRIMARY KEY (IdY )
)ENGINE=InnoDB;


#------------------------------------------------------------
# Table: Sondage
#------------------------------------------------------------

CREATE TABLE Sondage(
        Est_achete Bool ,
        frequence  Int DEFAULT 0,
        Type_Pers  Int NOT NULL ,
        Id         Int NOT NULL ,
        IdY        Int NOT NULL ,
        PRIMARY KEY (Id ,IdY )
)ENGINE=InnoDB;

#------------------------------------------------------------
# Table: Type
#------------------------------------------------------------

CREATE Type(
		IdT INT(11) Auto_increment NOT NULL,
		NomT Varchar(50) NOT NULL
)ENGINE=InnoDB;

#------------------------------------------------------------
# Table: Gout
#------------------------------------------------------------

CREATE Gout(
		IdG INT(11) Auto_increment NOT NULL,
		NomG Varchar(50) NOT NULL
)ENGINE=InnoDB;

ALTER TABLE Sondage ADD CONSTRAINT FK_Sondage_Id FOREIGN KEY (Id) REFERENCES Personne(Id);
ALTER TABLE Sondage ADD CONSTRAINT FK_Sondage_IdY FOREIGN KEY (IdY) REFERENCES Yaourt(IdY);
