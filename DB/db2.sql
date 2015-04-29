#------------------------------------------------------------
#        Script MySQL.
#------------------------------------------------------------


#------------------------------------------------------------
# Table: Personne
#------------------------------------------------------------

CREATE TABLE Personne(
        Id          int (11) Auto_increment  NOT NULL ,
        DateNaiss   Date NOT NULL ,
        Etat_civil  Varchar (25) NOT NULL ,
        Nb_personne Int NOT NULL ,
        Nb_enfant   Int NOT NULL ,
        Nb_Animaux  Int NOT NULL ,
        admin		Boolean,
        PRIMARY KEY (Id )
)ENGINE=InnoDB;


#------------------------------------------------------------
# Table: Yaourt
#------------------------------------------------------------

CREATE TABLE Yaourt(
        IdY    int (11) Auto_increment  NOT NULL ,
        Marque Varchar (50) NOT NULL ,
        Nom    Varchar (50) NOT NULL ,
        Type   Varchar (50) NOT NULL ,
        Gout   Varchar (50) NOT NULL ,
        PRIMARY KEY (IdY )
)ENGINE=InnoDB;


#------------------------------------------------------------
# Table: Sondage
#------------------------------------------------------------

CREATE TABLE Sondage(
        Est_connu  Bool ,
        Est_achete Bool ,
        frequence  Int ,
        Id         Int NOT NULL ,
        IdY        Int NOT NULL ,
        PRIMARY KEY (Id ,IdY )
)ENGINE=InnoDB;

ALTER TABLE Sondage ADD CONSTRAINT FK_Sondage_Id FOREIGN KEY (Id) REFERENCES Personne(Id);
ALTER TABLE Sondage ADD CONSTRAINT FK_Sondage_IdY FOREIGN KEY (IdY) REFERENCES Yaourt(IdY);
