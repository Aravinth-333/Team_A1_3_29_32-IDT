import cv2
import mediapipe as mp

# Initialize MediaPipe modules
mp_hands = mp.solutions.hands
mp_face = mp.solutions.face_mesh
mp_drawing = mp.solutions.drawing_utils

hands = mp_hands.Hands(min_detection_confidence=0.7, max_num_hands=1)
face_mesh = mp_face.FaceMesh(refine_landmarks=True)

cap = cv2.VideoCapture(0)

while True:
    ret, frame = cap.read()
    if not ret:
        break

    frame = cv2.flip(frame, 1)
    rgb = cv2.cvtColor(frame, cv2.COLOR_BGR2RGB)

    hand_results = hands.process(rgb)
    face_results = face_mesh.process(rgb)

    gesture_detected = False
    fingers_up = []
    eye_direction = ""

    # Gesture Recognition
    if hand_results.multi_hand_landmarks:
        for hand_landmarks in hand_results.multi_hand_landmarks:
            if hand_landmarks.landmark[8].y < hand_landmarks.landmark[6].y:
                fingers_up.append("Index")
            if hand_landmarks.landmark[12].y < hand_landmarks.landmark[10].y:
                fingers_up.append("Middle")
            mp_drawing.draw_landmarks(frame, hand_landmarks, mp_hands.HAND_CONNECTIONS)

    # Eye Tracking (detect if looking right or left)
    if face_results.multi_face_landmarks:
        for face_landmarks in face_results.multi_face_landmarks:
            left_eye_x = face_landmarks.landmark[474].x
            right_eye_x = face_landmarks.landmark[477].x
            nose_tip_x = face_landmarks.landmark[1].x

            if left_eye_x < nose_tip_x and right_eye_x < nose_tip_x:
                eye_direction = "Right"
            elif left_eye_x > nose_tip_x and right_eye_x > nose_tip_x:
                eye_direction = "Left"

            mp_drawing.draw_landmarks(frame, face_landmarks, mp_face.FACEMESH_TESSELATION)

    # Combined Action Logic
    if len(fingers_up) == 2:
        cv2.putText(frame, "Gesture: Light ON 💡", (10, 50), cv2.FONT_HERSHEY_SIMPLEX, 1, (0, 255, 0), 2)
        gesture_detected = True
    elif len(fingers_up) == 1 and eye_direction == "Left":
        cv2.putText(frame, "Gesture + Eye: Fan ON 🌀", (10, 90), cv2.FONT_HERSHEY_SIMPLEX, 0.8, (0, 200, 255), 2)
        gesture_detected = True
    elif eye_direction == "Right":
        cv2.putText(frame, "Eye Tracking: Looking Right → Light ON", (10, 130), cv2.FONT_HERSHEY_SIMPLEX, 0.7, (255, 200, 0), 2)
        gesture_detected = True

    if not gesture_detected:
        cv2.putText(frame, "Waiting for gesture or eye movement...", (10, 460), cv2.FONT_HERSHEY_SIMPLEX, 0.6, (200, 200, 200), 1)

    cv2.imshow("Smart Home Gesture & Eye Control Demo", frame)

    if cv2.waitKey(1) & 0xFF == ord('q'):
        break

cap.release()
cv2.destroyAllWindows()
