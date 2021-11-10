FROM openjdk:11
COPY target/Meal-Medicine-Delivery.jar mmd.jar
ENTRYPOINT ["java","-jar","/mmd.jar"]