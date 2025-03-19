# FDF - 42 Network Wireframe Renderer

FDF is a simple 3D wireframe renderer built as part of the 42 curriculum. It reads `.fdf` files containing 3D heightmap data, projects them into 2D space, and renders them using MiniLibX.

## 🖼️ Preview
<!-- Add an image or GIF of your FDF program running -->
![FDF Screenshot](https://private-user-images.githubusercontent.com/169259139/424619405-ceac2626-344d-4df1-8a89-f835b249143b.png?jwt=eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJpc3MiOiJnaXRodWIuY29tIiwiYXVkIjoicmF3LmdpdGh1YnVzZXJjb250ZW50LmNvbSIsImtleSI6ImtleTUiLCJleHAiOjE3NDI0MDY4MzksIm5iZiI6MTc0MjQwNjUzOSwicGF0aCI6Ii8xNjkyNTkxMzkvNDI0NjE5NDA1LWNlYWMyNjI2LTM0NGQtNGRmMS04YTg5LWY4MzViMjQ5MTQzYi5wbmc_WC1BbXotQWxnb3JpdGhtPUFXUzQtSE1BQy1TSEEyNTYmWC1BbXotQ3JlZGVudGlhbD1BS0lBVkNPRFlMU0E1M1BRSzRaQSUyRjIwMjUwMzE5JTJGdXMtZWFzdC0xJTJGczMlMkZhd3M0X3JlcXVlc3QmWC1BbXotRGF0ZT0yMDI1MDMxOVQxNzQ4NTlaJlgtQW16LUV4cGlyZXM9MzAwJlgtQW16LVNpZ25hdHVyZT0yY2YyOWFmZWJkZDI1ZmFiY2E2YTlhYzJiNDYyNTlhNTNlZGE0YWU5MGJmYzNmMmVmNjI4NzczNDQ3NzE0MTZkJlgtQW16LVNpZ25lZEhlYWRlcnM9aG9zdCJ9.l4pMknNj98PaQvozHwAx_Nja74jxcd-hdfyEpTHFq94)

## 🖼️  Preview
<!-- Add an image or GIF of your FDF program running -->
![FDF Screenshot](https://private-user-images.githubusercontent.com/169259139/424621390-7b65aaa6-1de0-4d0b-868a-f728d53404a0.png?jwt=eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJpc3MiOiJnaXRodWIuY29tIiwiYXVkIjoicmF3LmdpdGh1YnVzZXJjb250ZW50LmNvbSIsImtleSI6ImtleTUiLCJleHAiOjE3NDI0MDY5MzYsIm5iZiI6MTc0MjQwNjYzNiwicGF0aCI6Ii8xNjkyNTkxMzkvNDI0NjIxMzkwLTdiNjVhYWE2LTFkZTAtNGQwYi04NjhhLWY3MjhkNTM0MDRhMC5wbmc_WC1BbXotQWxnb3JpdGhtPUFXUzQtSE1BQy1TSEEyNTYmWC1BbXotQ3JlZGVudGlhbD1BS0lBVkNPRFlMU0E1M1BRSzRaQSUyRjIwMjUwMzE5JTJGdXMtZWFzdC0xJTJGczMlMkZhd3M0X3JlcXVlc3QmWC1BbXotRGF0ZT0yMDI1MDMxOVQxNzUwMzZaJlgtQW16LUV4cGlyZXM9MzAwJlgtQW16LVNpZ25hdHVyZT0xOTA1MDMyNTQ4NTNlNWI4ZTU5M2JjMGZkNTI5ZjM5MTEwM2U3YWRkMDk5NWNiOTA1OWFhZjhhZDMzY2RkZmNhJlgtQW16LVNpZ25lZEhlYWRlcnM9aG9zdCJ9.rqnqEsrMXEJwtMQsTWeSJoeGwCw9kxl96z6hlAZw0lY)

## 🖼️   Preview
<!-- Add an image or GIF of your FDF program running -->
![FDF Screenshot](https://private-user-images.githubusercontent.com/169259139/424622068-7a6348fc-9cce-48f7-bc19-5f3f9b66f180.png?jwt=eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJpc3MiOiJnaXRodWIuY29tIiwiYXVkIjoicmF3LmdpdGh1YnVzZXJjb250ZW50LmNvbSIsImtleSI6ImtleTUiLCJleHAiOjE3NDI0MDY1NjksIm5iZiI6MTc0MjQwNjI2OSwicGF0aCI6Ii8xNjkyNTkxMzkvNDI0NjIyMDY4LTdhNjM0OGZjLTljY2UtNDhmNy1iYzE5LTVmM2Y5YjY2ZjE4MC5wbmc_WC1BbXotQWxnb3JpdGhtPUFXUzQtSE1BQy1TSEEyNTYmWC1BbXotQ3JlZGVudGlhbD1BS0lBVkNPRFlMU0E1M1BRSzRaQSUyRjIwMjUwMzE5JTJGdXMtZWFzdC0xJTJGczMlMkZhd3M0X3JlcXVlc3QmWC1BbXotRGF0ZT0yMDI1MDMxOVQxNzQ0MjlaJlgtQW16LUV4cGlyZXM9MzAwJlgtQW16LVNpZ25hdHVyZT02MDk5MTA3NDlmZDFiYTgxZmUxOTU2NjZiYjg0YzEyNDczNjU4NThjZGE2NGJmOTNlNGI5YzgwNWMxYjYyZDJkJlgtQW16LVNpZ25lZEhlYWRlcnM9aG9zdCJ9.lWC1LcLRuC5isS2b7xpHolp3gkI_KBLDZOXz2ww4rVk)



## 📖 Features
- Parses `.fdf` map files to extract 3D points.
- Implements **isometric projection** for 3D visualization.
- Uses **Bresenham’s line algorithm** to draw connections between points.
- Keyboard controls for zoom, movement, and rotation.

## 🛠️ Installation

1. **Clone the repository:**
   ```sh
   git clone https://github.com/alaktari/FDF.git
   cd FDF

2. **Run the Project:**
for Mandatory:
   ```sh
   Make
   Make clean

for Bonus:
   ```sh
   Make Bonus
   Make clear
