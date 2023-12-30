-- MySQL dump 10.13  Distrib 8.0.33, for Win64 (x86_64)
--
-- Host: 127.0.0.1    Database: fitness_administration
-- ------------------------------------------------------
-- Server version	8.0.33

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!50503 SET NAMES utf8 */;
/*!40103 SET @OLD_TIME_ZONE=@@TIME_ZONE */;
/*!40103 SET TIME_ZONE='+00:00' */;
/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;

--
-- Table structure for table `employee`
--

DROP TABLE IF EXISTS `employee`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `employee` (
  `id` int NOT NULL AUTO_INCREMENT,
  `fname` varchar(45) NOT NULL,
  `lname` varchar(45) NOT NULL,
  `age` int NOT NULL,
  `weight` float NOT NULL,
  `height` float NOT NULL,
  `birthdate` varchar(10) NOT NULL,
  `basesalary` float NOT NULL DEFAULT '11402.3',
  `startingdate` varchar(10) NOT NULL,
  `leavingdate` varchar(10) DEFAULT NULL,
  `employeetype` varchar(45) DEFAULT NULL,
  `offdays` int NOT NULL DEFAULT '0',
  `workdays` int NOT NULL,
  PRIMARY KEY (`id`),
  UNIQUE KEY `id_UNIQUE` (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=12 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `employee`
--

LOCK TABLES `employee` WRITE;
/*!40000 ALTER TABLE `employee` DISABLE KEYS */;
INSERT INTO `employee` VALUES (1,'Petra','Delisium',34,72,165,'15/09/2002',35000,'10/03/2022','N/A','egitmen',0,10),(2,'Alice','Smith',28,65.5,170,'12/05/1995',15000,'03/10/2022','N/A','temizlikci',0,22),(3,'John','Doe',35,72.8,180,'08/21/1987',25000,'11/15/2022','N/A','gorevli',0,18),(4,'Emma','Johnson',42,68.2,165,'05/19/1980',35000,'07/02/2022','N/A','egitmen',0,25),(5,'Michael','Brown',31,80,175,'02/14/1992',15000,'09/28/2022','N/A','temizlikci',0,20),(6,'Sophia','Miller',27,60.7,160,'10/08/1996',25000,'04/03/2022','N/A','gorevli',0,23),(7,'William','Clark',40,78.3,185,'07/30/1983',35000,'06/12/2022','N/A','egitmen',0,15),(8,'Olivia','Taylor',33,68.9,175,'09/25/1989',15000,'01/22/2023','N/A','temizlikci',0,19),(10,'Ava','White',38,71.5,167,'12/02/1984',35000,'05/07/2022','N/A','egitmen',0,17),(11,'Liam','Thomas',26,68,172,'11/14/1997',15000,'02/04/2023','N/A','temizlikci',0,24);
/*!40000 ALTER TABLE `employee` ENABLE KEYS */;
UNLOCK TABLES;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2023-12-30 22:29:33
