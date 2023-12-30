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
-- Table structure for table `member`
--

DROP TABLE IF EXISTS `member`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `member` (
  `id` int NOT NULL AUTO_INCREMENT,
  `fname` varchar(45) NOT NULL,
  `lname` varchar(45) NOT NULL,
  `age` int NOT NULL,
  `weight` float NOT NULL,
  `height` float NOT NULL,
  `birthdate` varchar(10) NOT NULL,
  `membertype` varchar(8) NOT NULL,
  `regdate` varchar(10) DEFAULT NULL,
  `xp` float NOT NULL DEFAULT '0',
  `email` varchar(80) DEFAULT NULL,
  `balance` float NOT NULL DEFAULT '0',
  `wgoal` float DEFAULT NULL,
  `username` varchar(45) NOT NULL,
  `password` varchar(45) NOT NULL,
  PRIMARY KEY (`id`),
  UNIQUE KEY `id_UNIQUE` (`id`),
  UNIQUE KEY `username_UNIQUE` (`username`)
) ENGINE=InnoDB AUTO_INCREMENT=89 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `member`
--

LOCK TABLES `member` WRITE;
/*!40000 ALTER TABLE `member` DISABLE KEYS */;
INSERT INTO `member` VALUES (1,'NULL','NULL',20,100,180,'01/01/0001','diamond','30/12/2023',0,'nulltest@gmail.com',0,80,'nullusr','nullpw'),(68,'John','Doe',25,70,175,'15/05/1990','gold','30/12/2023',31200,'john.doe@gmail.com',1000,65,'john_doe123','securePass123'),(69,'Alice','Smith',30,55,160,'22/08/1985','diamond','30/12/2023',45000,'alice.smith@gmail.com',200,50,'alice_s','password123'),(70,'Michael','Johnson',28,80,180,'10/11/1993','platinum','30/12/2023',26500,'michael.j@gmail.com',1200,75,'mike_87','pass@word'),(71,'Emily','Brown',35,65,168,'05/04/1988','diamond','30/12/2023',38000,'emily.b@gmail.com',2000,60,'em_brown','securePwd456'),(72,'Daniel','Miller',22,75,185,'18/09/1999','gold','30/12/2023',42000,'daniel.miller@gmail.com',800,70,'dan_m','pass1234'),(73,'Sophia','Wilson',27,58,162,'30/07/1994','platinum','30/12/2023',28320,'sophia.w@gmail.com',1300,55,'s_wilson','securePass567'),(75,'Emma','Taylor',29,63,170,'25/06/1992','diamond','30/12/2023',49000,'emma.taylor@gmail.com',1600,45,'emma_t','securePwd789'),(76,'Ryan','Clark',26,72,178,'08/12/1997','platinum','30/12/2023',35000,'ryan.clark@gmail.com',600,68,'ryan_c','pass7890'),(79,'Matthew','Robinson',24,78,183,'14/10/1998','platinum','30/12/2023',42040,'matthew.robinson@gmail.com',1500,72,'m_robinson','pass123'),(80,'Chloe','Baker',28,60,165,'19/07/1993','diamond','30/12/2023',32000,'chloe.baker@gmail.com',1800,52,'chloe_b','securePwd456'),(81,'Nicholas','White',29,85,188,'27/02/1992','gold','30/12/2023',48000,'nicholas.white@gmail.com',1200,77,'n_white','password789'),(82,'Ava','Hill',33,55,160,'08/04/1989','platinum','30/12/2023',38500,'ava.hill@gmail.com',1400,48,'ava_h','pass890'),(83,'Ethan','Turner',26,70,175,'25/11/1996','platinum','30/12/2023',35500,'ethan.turner@gmail.com',1300,68,'ethan_t','securePass123'),(84,'Isabella','Cooper',30,62,167,'02/09/1991','diamond','30/12/2023',28225,'isabella.cooper@gmail.com',1600,55,'isabella_c','pass5678'),(85,'Mason','Evans',27,75,180,'16/06/1994','gold','30/12/2023',45000,'mason.evans@gmail.com',1400,70,'m_evans','securePwd890'),(86,'Grace','Parker',32,65,170,'11/03/1988','diamond','30/12/2023',30000,'grace.parker@gmail.com',600,60,'grace_p','password1234'),(88,'Avery','Fisher',31,68,175,'06/01/1992','gold','30/12/2023',39000,'avery.fisher@gmail.com',2000,65,'avery_f','securePass5678');
/*!40000 ALTER TABLE `member` ENABLE KEYS */;
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
