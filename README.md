# Ürün Yönetimi Konsol Uygulaması (C Projesi)

Bu C konsol uygulaması, bir dosyada saklanan ürün listesini yönetmek için tasarlanmıştır.  
Bağlı liste (linked list) kullanarak ürünleri tutar ve çeşitli işlemler yapmanıza olanak sağlar.

## 🔹 Özellikler
1. **Ürün Listesini Göster**  
   Tüm ürünleri adı, birim fiyatı, adeti, satış fiyatı, kategorisi ve kar oranı ile görüntüler.

2. **Kategoriye Göre Silme**  
   Belirli bir kategoriye ait tüm ürünleri siler.

3. **En Yüksek Kar Oranlı Ürünü Silme**  
   En yüksek kar oranına sahip ürünü bulur ve listeden siler.

4. **İstenilen Sıraya Yeni Ürün Ekleme**  
   Bağlı listeye kullanıcı tarafından belirlenen sıraya yeni bir ürün ekler.

5. **Satış Fiyatını Güncelleme**  
   Kullanıcı tarafından seçilen sıradaki ürünün satış fiyatını günceller.

6. **Çıkış**  
   Programı güvenli bir şekilde sonlandırır.

---

## 🧾 Gereksinimler
- C derleyici (GCC veya eşdeğer)  
- `urun.txt` dosyası ile ürün verisi

---

## 📂 Örnek `urun.txt` Formatı
Dosyadaki her satır, virgül ile ayrılmış şekilde aşağıdaki formatta olmalıdır:
UrunAdi,BirimFiyat,Adet,SatisFiyati,Kategori
 **Not:** Program başlatıldığında bu dosyayı okur. Dosya yoksa çalışmaz.
