from skimage import io
import matplotlib.pyplot as plt
import cv2
import numpy as np


def distance(point1, point2):
    return abs(point1[0] - point2[0]) ** 2 + abs(point1[1] - point2[1])


def remove_points_from_arr(points, arr):
    res = []
    for count in range(0, len(arr)):
        if count in points:
            continue
        else:
            res.append(arr[count])
    return res


def get_critical_points(contour):
    max_x = 0
    max_y = 0
    min_x = 0
    min_y = 0

    for count in contour:
        if count[0][0] > max_x:
            max_x = count[0][0]
        elif count[0][0] < min_x:
            min_x = count[0][0]

        if count[0][1] > max_y:
            max_y = count[0][1]
        elif count[0][1] < min_y:
            min_y = count[0][1]
    return [max_x, min_x, max_y, min_y]


# funkcja zmieniająca tablicę typu  [[x1, y1, z1][x2, y2, z2]...] na tablicę typu [[x1, x2...][y1, y2...]...]
def change_shape(arr):
    try:
        res = []
        for num in range(0, len(arr[0])):
            res.append([])

        for f in arr:
            for num in range(0, len(f)):
                res[num].append(f[num])

        return res

    except IndexError:
        print(np.shape(arr))


def gamma(img):
    g = np.mean(img)
    return img ** g


def contrast(img):
    percmin = 0.3
    percmax = 2.0
    MIN = np.percentile(img, percmin)
    MAX = np.percentile(img, 100 - percmax)
    norm = (img - MIN) / (MAX - MIN)
    norm[norm[:, :] > 1] = 1
    norm[norm[:, :] < 0] = 0
    return norm * 255


# Tutaj będzie zabawy z parametrami
# intensity - agresywność rozmycia Gaussa
# percent - percentyle zdjęcia użyte do wykrywania krawędzi metodą Canny'ego
# można też spróbować dopasować contourArea w tym ifie,
# coby odfiltrowało najmniejsze/największe zaznaczone (i najprawdopodobniej - niepotrzebne) krawędzie
# Jebla idzie dostać
# Trzymajcie się na tych KCK'ach

def prepare_photo(photo):
    intensity = 3
    kernel = np.ones((intensity, intensity), np.float32) / intensity ** 2

    work = cv2.cvtColor(photo, cv2.COLOR_BGR2GRAY)
    work = np.uint8(contrast(work))
    work = cv2.filter2D(work, -1, kernel)

    percent = np.percentile(work, [5, 60])

    work = cv2.Canny(work, percent[0], percent[1])
    contour_array, _ = cv2.findContours(work, cv2.RETR_TREE, cv2.CHAIN_APPROX_NONE)

    contours = []
    centroid_array = []

    contour_areas = [cv2.contourArea(x) for x in contour_array]

    # Akceptowalne rozmiary konturów:
    max_area = 1.5 * np.percentile(contour_areas, 80)
    min_area = 0.5 * np.percentile(contour_areas, 40)

    # Odseparowywanie konturów:
    for XD in contour_array:
        contour_area = cv2.contourArea(XD)
        if min_area < contour_area < max_area:
            ellipse = cv2.fitEllipse(XD)
            ellipse_area = ellipse[1][0] * ellipse[1][1] * 3.14 / 4

            if 0.6 * ellipse_area < contour_area < 1.3 * ellipse_area:
                cv2.ellipse(photo, ellipse, (255, 0, 0), 3)
                avg = np.sum(XD, axis=0) / len(XD)
                centroid_array.append(avg[0])
                contours.append(XD)

    cv2.drawContours(photo, contours, -1, (0, 255, 0), 1)

    return photo, centroid_array

#   ] \      / [        /\        ][   ] \     ][
#   ][\\    //][       //\\       ][   ][\\    ][
#   ][ \\  // ][      //  \\      ][   ][ \\   ][
#   ][  \\//  ][     //    \\     ][   ][  \\  ][
#   ][        ][    //======\\    ][   ][   \\ ][
#   ][        ][   //        \\   ][   ][    \\][
#   ][        ][  //          \\  ][   ][     \ [


if __name__ == '__main__':
    filenames = []

    for i in range(1, 12):
        filenames.append(str(i))

    filenames.append("kostka")

    images = [cv2.imread('./data/' + i + '.jpg') for i in filenames]

    for i in range(0, len(filenames)):
        plt.clf()
        print(filenames[i] + ".txt")

        xD, centroids = prepare_photo(images[i])

        to_remove = []

        # Usuwanie centroidów, które są zbyt blisko
        for x in range(0, len(centroids)):
            if x in to_remove:
                continue
            for y in range(x + 1, len(centroids)):
                try:
                    if distance(centroids[x], centroids[y]) < 30:
                        to_remove.append(y)
                except IndexError:
                    print(x, y, len(centroids))

        centroids = remove_points_from_arr(to_remove, centroids)

        font = cv2.FONT_HERSHEY_SIMPLEX
        bottomLeftCornerOfText = (10, 30)
        fontScale = 1
        fontColor = (255, 0, 0)
        lineType = 2

        # Przerobienie tablicy na kształt odpowiedni do plotowania
        # (z tablicy rozmiarów n x 2 do tablicy o rozmiarze 2 x n)
        centroids = change_shape(centroids)
        cv2.putText(xD, 'Ilosc oczek: {0}'.format(len(centroids[0])),
                    bottomLeftCornerOfText, font, fontScale, fontColor, lineType)
        plt.plot(centroids[0], centroids[1], 'o', markersize=5, color="#ff00ff")

        io.imshow(cv2.cvtColor(xD, cv2.COLOR_BGR2RGB))

        plt.savefig('./Preprocessed/' + filenames[i] + '.png')
