# cap_leg_measure

Görüntü işleme projesinde  öncelikle bir ROI (İlgilenilen Bölge) belirlendi ve 
bu bölgede kenar tespiti için Canny fonksiyonunu kullanıldı. Daha sonra, 
kenarları daha iyi belirlemek için genişletme işlemi uygulandı. Ardından, 
genişletilmiş kenarların konturunu tespit etmek için OpenCV'nin findContours fonksiyonunu kullanıldı.
Konturların en alt noktalarını bulup bu noktaların 20 piksel üstlerine iki adet nokta koyarak,
bu noktalar arasına bir line çizildi. Noktalar arası mesafeyi hesaplayarak, bu mesafeyi  putText fonksiyonu yardımıyla line üzerine yazdırıldı ve 
programın toplam çalışma süresi hesaplandı. Kısacası bu program bir gripper tarafınfan tutulan kapasitörün
bacakları arasındaki mesafeyi px cinsinden ölçmek için kullanılır.  
 
