-- MySQL dump 10.15  Distrib 10.0.17-MariaDB, for Linux (x86_64)
--
-- Host: localhost    Database: game_db
-- ------------------------------------------------------
-- Server version	10.0.17-MariaDB-log

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8 */;
/*!40103 SET @OLD_TIME_ZONE=@@TIME_ZONE */;
/*!40103 SET TIME_ZONE='+00:00' */;
/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;

--
-- Table structure for table `users`
--

DROP TABLE IF EXISTS `users`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `users` (
  `id` int(32) unsigned NOT NULL AUTO_INCREMENT,
  `login` varchar(120) NOT NULL,
  `lastVisit` datetime DEFAULT NULL,
  `xPosition` int(32) DEFAULT NULL,
  `yPosition` int(32) DEFAULT NULL,
  `zPosition` int(4) DEFAULT NULL,
  `isOnline` tinyint(1) DEFAULT NULL,
  PRIMARY KEY (`id`),
  UNIQUE KEY `login` (`login`)
) ENGINE=InnoDB AUTO_INCREMENT=24 DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `users`
--

LOCK TABLES `users` WRITE;
/*!40000 ALTER TABLE `users` DISABLE KEYS */;
INSERT INTO `users` VALUES (1,'Gettor','2015-03-11 22:45:56',20,20,0,0),(2,'SirWojtek','2015-03-11 22:46:11',10,10,0,0),(3,'RandomDude','2015-03-11 22:46:28',30,15,0,0),(4,'User0','2015-04-25 17:07:53',50,50,0,0),(5,'User1','2015-04-25 17:09:07',50,50,0,0),(6,'User2','2015-04-25 17:09:07',50,50,0,0),(7,'User3','2015-04-25 17:09:07',50,50,0,0),(8,'User4','2015-04-25 17:09:07',50,50,0,0),(9,'User5','2015-04-25 17:09:07',50,50,0,0),(10,'User6','2015-04-25 17:09:07',50,50,0,0),(11,'User7','2015-04-25 17:09:07',50,50,0,0),(12,'User8','2015-04-25 17:09:07',50,50,0,0),(13,'User9','2015-04-25 17:09:07',50,50,0,0),(14,'User10','2015-04-25 17:09:07',50,50,0,0),(15,'User11','2015-04-25 17:09:07',50,50,0,0),(16,'User12','2015-04-25 17:09:07',50,50,0,0),(17,'User13','2015-04-25 17:09:07',50,50,0,0),(18,'User14','2015-04-25 17:09:07',50,50,0,0),(19,'User15','2015-04-25 17:09:07',50,50,0,0),(20,'User16','2015-04-25 17:09:07',50,50,0,0),(21,'User17','2015-04-25 17:09:07',50,50,0,0),(22,'User18','2015-04-25 17:09:07',50,50,0,0),(23,'User19','2015-04-25 17:09:07',50,50,0,0);
/*!40000 ALTER TABLE `users` ENABLE KEYS */;
UNLOCK TABLES;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2015-04-25 17:10:08
