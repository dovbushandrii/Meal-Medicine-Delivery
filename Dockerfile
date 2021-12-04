FROM openjdk:11
COPY target/Meal-Medicine-Delivery.jar app.jar
COPY meal.jpg meal.jpg
COPY pills.jpg pills.jpg
ENTRYPOINT ["java","-jar","/app.jar"]