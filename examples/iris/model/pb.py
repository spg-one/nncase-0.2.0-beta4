import tensorflow as tf

# 加载 TensorFlow Lite 模型
interpreter = tf.lite.Interpreter(model_path="iris.tflite")
interpreter.allocate_tensors()

# 获取输入和输出张量的详细信息
input_details = interpreter.get_input_details()
output_details = interpreter.get_output_details()

# 创建一个空白的 TensorFlow 图
graph_def = tf.compat.v1.GraphDef()

# 遍历输入和输出张量的详细信息，并添加到 TensorFlow 图中
for input_detail in input_details:
    tensor_name = input_detail["name"]
    tensor_shape = input_detail["shape"]
    placeholder_node = tf.compat.v1.NodeDef()
    placeholder_node.op = "Placeholder"
    placeholder_node.name = tensor_name
    placeholder_node.attr["dtype"].type = tf.float32.as_datatype_enum
    placeholder_node.attr["shape"].shape.CopyFrom(tf.TensorShape(tensor_shape).as_proto())
    graph_def.node.extend([placeholder_node])

for output_detail in output_details:
    tensor_name = output_detail["name"]
    graph_def.node.add(op="Identity", name=tensor_name, input=tensor_name)

# 将 TensorFlow 图保存为 .pb 文件
with tf.io.gfile.GFile("converted_model.pb", "wb") as f:
    f.write(graph_def.SerializeToString())
